
#include <gtest/gtest.h>

#include "get_next.hpp"

//for testing purposes
#include <list>
#include <forward_list>
#include <string>
#include <map>

//#define COMPILE_TIME_FAILURE

using namespace itertools;

using NumericListTypes = testing::Types<
		std::vector<int>,
		std::list<int>,
        std::forward_list<int>
>;

template<typename T>
class NumericListTest : public testing::Test {};
TYPED_TEST_SUITE(NumericListTest, NumericListTypes);

TYPED_TEST(NumericListTest, BasicTest) {
	using List = TypeParam;
	List
	        v1 {1,8,15,16,35},
			v2 {2,7,12,63},
			v3 {10,13,14,42};

	std::ostringstream os;

	IterPair<List>
		p1 {v1.begin(), v1.end()},
		p2 {v2.begin(), v2.end()},
		p3 {v3.begin(), v3.end()};
	for (auto it = GetNext<List>(p1, p2, p3);
	        isNotEnd<List>(it);
			it = GetNext<List>(p1, p2, p3))
	{
		os << *it << ' ';
	}
	std::string check {"1 2 7 8 10 12 13 14 15 16 35 42 63 "};
	ASSERT_EQ(os.str(), check);
}

TYPED_TEST(NumericListTest, OneIsEmpty) {
	using List = TypeParam;
	List
	        v1 {1,8,15,16,35},
			v2 {},
			v3 {10,13,14,42};

	std::ostringstream os;

	IterPair<List>
		p1 {v1.begin(), v1.end()},
		p2 {v2.begin(), v2.end()},
		p3 {v3.begin(), v3.end()};
	for (auto it = GetNext<List>(p1, p2, p3);
			isNotEnd<List>(it);
			it = GetNext<List>(p1, p2, p3))
	{
		os << *it << ' ';
	}
	std::string check {"1 8 10 13 14 15 16 35 42 "};
	ASSERT_EQ(os.str(), check);
}

TYPED_TEST(NumericListTest, AllAreEmpty) {
	using List = TypeParam;
	List
			v1 {},
			v2 {},
			v3 {};

	std::ostringstream os;

	IterPair<List>
			p1 {v1.begin(), v1.end()},
			p2 {v2.begin(), v2.end()},
			p3 {v3.begin(), v3.end()};
	for (auto it = GetNext<List>(p1, p2, p3);
	     isNotEnd<List>(it);
	     it = GetNext<List>(p1, p2, p3))
	{
		os << *it << ' ';
	}
	ASSERT_TRUE(os.str().empty());
}

TEST(SymbolList, BasicTest) {
	using List = std::string;
	List
			v1 {"ade"},
			v2 {"bkm"},
			v3 {"cz"};

	std::ostringstream os;

	IterPair<List>
			p1 {v1.begin(), v1.end()},
			p2 {v2.begin(), v2.end()},
			p3 {v3.begin(), v3.end()};
	for (auto it = GetNext<List>(p1, p2, p3);
	     isNotEnd<List>(it);
	     it = GetNext<List>(p1, p2, p3))
	{
		os << *it << ' ';
	}
	std::string check {"a b c d e k m z "};
	ASSERT_EQ(os.str(), check);
}

TEST(MappedList, BasicTest) {
	using List = std::map<int, int>;
	List
			v1 {{1, 0},{8, 0},{15, 0},{16, 0},{35, 0}},
			v2 {{2, 0},{7, 0},{12, 0},{63, 0}},
			v3 {{10, 0},{13, 0},{14, 0},{42, 0}};

	std::ostringstream os;

	IterPair<List>
			p1 {v1.begin(), v1.end()},
			p2 {v2.begin(), v2.end()},
			p3 {v3.begin(), v3.end()};
	for (auto it = GetNext<List>(p1, p2, p3);
	     isNotEnd<List>(it);
	     it = GetNext<List>(p1, p2, p3))
	{
		os << it->first << ' ';
	}
	std::string check {"1 2 7 8 10 12 13 14 15 16 35 42 63 "};
	ASSERT_EQ(os.str(), check);
}

#ifdef COMPILE_TIME_FAILURE
TEST(SymbolList, BasicTestCompileTimeFailure) {
	using List = std::string;
	List
			v1 {"ade"},
			v3 {"cz"};

	IterPair<List>
			p1 {v1.begin(), v1.end()},
			p3 {v3.begin(), v3.end()};
	auto it = GetNext<List>(p1, p3);
	ASSERT_TRUE(true);
}
#endif

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
	testing::InitGoogleTest(&argc, argv);
	testing::GTEST_FLAG(color) = "yes";

	return RUN_ALL_TESTS();
}
