#define BOOST_TEST_MODULE Allocator_test_module

#include <Allocator/Allocator.h>
#include <Allocator/List.h>
#include <algorithm>
#include <map>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Allocator_test_suite)

BOOST_AUTO_TEST_CASE(Allocator_stdVectorInt)
{  
    constexpr size_t N = 16;
    std::vector<int, Allocator::Allocator<int, N>> vec;
    for (size_t i = 0; i < N/2; ++i) {
        vec.push_back(42);
    }
    BOOST_CHECK(std::all_of(vec.begin(), vec.end(), 
           [](int a){ return a == 42;}));
}

BOOST_AUTO_TEST_CASE(Allocator_stdMapInt)
{  
    constexpr size_t N = 10;
    std::map<int, int, std::less<int>, 
            Allocator::Allocator<std::pair<const int, int>, N>> mm;
    for (size_t i = 0; i < N; ++i) {
        mm[i] = i+42;
    }
    for (int i = 0; i < N; ++i) {
        BOOST_CHECK(mm.at(i) == (i+42));
    }
}

BOOST_AUTO_TEST_CASE(List_stdAllocator)
{  
    Allocator::List<int> l;
    constexpr int N = 10;
    for (int i = 0; i < N; ++i) {
        l.push_back(i);
    }
    int i = 0;
    for (auto it = l.begin(); it != l.end(); ++it, ++i) {
        BOOST_CHECK(*it == i);
    }
}

BOOST_AUTO_TEST_CASE(List_CustomAllocator)
{  
    constexpr size_t N = 9;
    Allocator::List<int, Allocator::Allocator<int, N+1>> l;
    for (int i = 0; i < N; ++i) {
        l.push_back(i);
    }
    int i = 0;
    for (auto it = l.begin(); it != l.end(); ++it, ++i) {
        BOOST_CHECK(*it == i);
    }
}

BOOST_AUTO_TEST_SUITE_END()

