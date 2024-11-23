//
// Created by Andrey Solovyev on 23.11.2024.
//

#pragma once

#include <vector>
#include <queue>
#include <utility>

namespace itertools {

	template<typename L>
	concept IsList = requires(L l) {
		l.begin();
		l.end();
		typename L::value_type;
		typename L::iterator;
	};

	template<IsList List>
	using Iter = typename List::iterator;

	template<IsList List>
	using IterPair = std::pair<Iter<List>, Iter<List>>;

	template<IsList List>
	auto isOk = [](IterPair<List> p){
		return p.first != p.second;
	};

	template<IsList List>
	static inline List emptyList {};

	template<IsList List>
	static inline Iter<List> sentinel = emptyList<List>.end();

	template<IsList List>
	auto isNotEnd = [](Iter<List> iter){
		return iter != sentinel<List>;
	};

	template <typename MaybeMap>
	concept IsMap = requires () {
		typename MaybeMap::key_type;
		typename MaybeMap::mapped_type;
		typename MaybeMap::value_type;
	};

	template<typename C>
	inline constexpr bool isMap { IsList<C> && IsMap<C> };

	struct KeyExtractor {
		template <IsList List>
		auto& dereferenceIter(Iter<List> iter) const noexcept {
			if constexpr (isMap<List>) {
				return iter->first;
			} else {
				return *iter;
			}
		}
	};
	static constexpr inline KeyExtractor keyExtractor;

}//!namespace

using namespace itertools;

template <IsList List, typename... IteratorPairs>
requires (std::same_as<IterPair<List>, IteratorPairs>, ...)
/**
 * @dev
 * the nex requirement is a part of task statement, see "readme.md"
 * */
&& (requires {requires sizeof...(IteratorPairs) == 3u;} )
Iter<List> GetNext(IteratorPairs& ...pairs) {
	auto do_nothing = [](){ /* do nothing */};

	auto cmp = [](IterPair<List> lhs, IterPair<List> rhs){
		return
			keyExtractor.template dereferenceIter<List>(lhs.first) >
			keyExtractor.template dereferenceIter<List>(rhs.first);
	};

	using PQ = std::priority_queue<IterPair<List>, std::vector<IterPair<List>>, decltype(cmp)>;

	/**
	 * @dev
	 * This PQ can be undone "static" or can be placed at arena using std::pmr.
	 * Currently it is "static" to avoid calling "new" every func call, that may be expensive.
	 */
	static PQ pq;

	((isOk<List>(pairs) ? pq.push(pairs) : do_nothing()),...);
	if (pq.empty()) return sentinel<List>;
	auto [nextIter, _] = pq.top();
	while(!pq.empty()) pq.pop();
	((nextIter == pairs.first ? ++pairs.first : sentinel<List>),...);


	return nextIter;
}
