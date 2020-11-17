#define BOOST_TEST_MODULE IpFilter_test_module

#include <IpFilter/IpFilter.h>

#include <boost/test/unit_test.hpp>
#include <sstream>
#include <iostream>

using namespace IpFilter;

BOOST_AUTO_TEST_SUITE(IpFilter_test_suite)

 BOOST_AUTO_TEST_CASE(IpFilter_IpAddressPrintout)
 {
     std::stringstream ss;
     IpAddress ip{1,2,3,4};
     ss << ip;
     BOOST_CHECK_MESSAGE("1.2.3.4", ss.str());
 }

 BOOST_AUTO_TEST_CASE(IpFilter_IpAddressCompare)
 {
     std::stringstream ss;
     IpAddress ip{1,2,1,1}, ip2{1,10,1,1};
     BOOST_CHECK(ip > ip2);
     BOOST_CHECK(ip2 < ip);
 }

 BOOST_AUTO_TEST_CASE(IpFilter_IpAddressIn)
 {   
     IpAddress ip;
    
     std::stringstream ss;
     ss << "1.2.3.255";
     IpAddress result{1,2,3,255};
     ss >> ip;
     BOOST_CHECK(ip == result);
     ss.clear();
     // incorrect ip bytes
     ss << "1.1.256.1";
     BOOST_REQUIRE_THROW({ss>>ip;},std::out_of_range);
     ss.clear();
     ss << "a.256.0.1";
     BOOST_REQUIRE_THROW({ss>>ip;},std::out_of_range);
 }

 BOOST_AUTO_TEST_CASE(IpFilter_IpPoolPrintOut)
 {   
     IpPool ip_pool(std::vector<IpAddress>({{1,2,3,4},{2,3,4,5}}));
     std::stringstream ss;
     ss << ip_pool;
     BOOST_CHECK("1.2.3.4\n2.3.4.5\n" == ss.str());
 }

BOOST_AUTO_TEST_CASE(IpFilter_IpPoolIn)
{
    IpPool ip_pool;
    std::stringstream ss;
    ss << "1.2.3.4\tnot_used\tnot_used\n";
    ss << "2.3.4.5\tnot_used\tnot_used\n";
    ss >> ip_pool;
    BOOST_CHECK(std::vector<IpAddress>({{1,2,3,4},{2,3,4,5}}) == ip_pool);
}

BOOST_AUTO_TEST_CASE(IpFilter_IpPoolOut)
{
    IpPool ip_pool;
    std::stringstream ss;
    ss << "1.1.1.1\tnot_used\tnot_used\n";
    ss << "1.10.1.1\tnot_used\tnot_used\n";
    ss << "1.2.1.1\tnot_used\tnot_used\n";
    ss >> ip_pool;
    ip_pool.Sort();
    BOOST_CHECK(std::vector<IpAddress>({{1,10,1,1},{1,2,1,1}, {1,1,1,1}}) == ip_pool);
}

BOOST_AUTO_TEST_CASE(IpFilter_IpPoolSort)
{
    IpPool ip_pool;
    std::stringstream ss;
    ss << "1.1.1.1\tnot_used\tnot_used\n";
    ss << "1.10.1.1\tnot_used\tnot_used\n";
    ss << "1.2.1.1\tnot_used\tnot_used\n";
    ss >> ip_pool;
    ip_pool.Sort();
    BOOST_CHECK(std::vector<IpAddress>({{1,10,1,1},{1,2,1,1}, {1,1,1,1}}) == ip_pool);
}

BOOST_AUTO_TEST_CASE (IpFilter_VariadicFilter)
{
    using namespace std;
    ostringstream output;
    {   
        ostringstream output;
        IpPool pool(vector<IpAddress>(
                    {{2,1,6,9},
                    {1,46,8,2},
                    {1,10,1,1},
                    {1,2,1,1},
                    {1,1,1,1}
        }));
        auto result = pool.Filter(1, 1);
        std::string expected_value("1.1.1.1\n");
        output << result;
        BOOST_CHECK_MESSAGE(expected_value == output.str(),
                            "your output: " + output.str() +
                            "\nexpected print:\n" + expected_value);
    }
    {
        ostringstream output;
        IpPool pool(vector<IpAddress>({
                        {2,1,6,9},
                        {1,46,8,2},
                        {1,10,1,1},
                        {1,2,1,1},
                        {1,1,1,1},
                        {0, 3, 7, 10},
        }));
        auto result = pool.Filter(1);
        std::string expected_value("1.46.8.2\n1.10.1.1\n1.2.1.1\n1.1.1.1\n");
        output << result;
        BOOST_CHECK_MESSAGE(expected_value == output.str(),
                            "your output: " + output.str() +
                            "\nexpected print:\n" + expected_value);
    }
    {
        IpPool pool(vector<IpAddress>({
                        {2,1,6,9},
                        {1,46,8,2},
                        {1,10,1,1},
                        {1,2,1,1},
                        {1,1,1,1},
                        {0, 3, 7, 10},
        }));
        
        auto result = pool.Filter(2);
        std::string expected_value("2.1.6.9\n");
        output << result;
        BOOST_CHECK_MESSAGE(expected_value == output.str(),
                            "your output: " + output.str() +
                            "\nexpected print:\n" + expected_value);
    }   
}

BOOST_AUTO_TEST_CASE (IpFilter_FilterAny)
{
    using namespace std;
    ostringstream output;
    IpPool pool(vector<IpAddress>(
                {{2,1,6,9},
                {1,46,8,2},
                {1,10,1,1},
                {46,46,46,1},
                {1,46,1,46}
    }));
    auto result = pool.FilterAny(46);
    std::string expected_value("1.46.8.2\n46.46.46.1\n1.46.1.46\n");
    output << result;
    BOOST_CHECK_MESSAGE(expected_value == output.str(),
                        "your output: " + output.str() +
                        "\nexpected print:\n" + expected_value); 
}

BOOST_AUTO_TEST_SUITE_END()

