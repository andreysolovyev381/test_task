//
// Created by Andrey Solovyev on 23.11.2024.
//

#pragma once

#include <concepts>
#include <vector>
#include <queue>
#include <utility>

namespace itertools {

	template<typename MaybeList>
	concept IsList = requires(MaybeList maybeList) {
		maybeList.begin();
		maybeList.end();
		typename MaybeList::value_type;
		typename MaybeList::iterator;
	};

	template<IsList List>
	using Iter = typename List::iterator;

	template<IsList List>
	using IterPair = std::pair<Iter<List>, Iter<List>>;

	template<IsList List>
	auto isDereferencable = [](IterPair<List> p){
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


template <itertools::IsList List, typename... IteratorPairs>
requires (std::same_as<itertools::IterPair<List>, IteratorPairs>, ...)
/**
 * @dev
 * the next requirement is a part of task statement, see "readme.md"
 * */
&& (requires {requires sizeof...(IteratorPairs) == 3u;} )
itertools::Iter<List> GetNext(IteratorPairs& ...pairs) {
	using namespace itertools;

	auto do_nothing = [](){ /* do nothing */};

	using CmpType = decltype([](IterPair<List> lhs, IterPair<List> rhs){
		return
			keyExtractor.template dereferenceIter<List>(lhs.first) >
			keyExtractor.template dereferenceIter<List>(rhs.first);
	});

	using PQ = std::priority_queue<IterPair<List>, std::vector<IterPair<List>>, CmpType>;

	/**
	 * @dev
	 * This PQ can be undone "static" or can be placed at arena using std::pmr.
	 * Currently it is "static" to avoid calling "new" every func call, that may be expensive in this context.
	 * Indeed, it turns out to be thread unsafe.
	 */
	static PQ pq;

	((isDereferencable<List>(pairs) ? pq.push(pairs) : do_nothing()),...);
	if (pq.empty()) return sentinel<List>;
	auto [nextIter, _] = pq.top();
	while(!pq.empty()) pq.pop();
	((nextIter == pairs.first ? ++pairs.first : sentinel<List>),...);

	return nextIter;
}
