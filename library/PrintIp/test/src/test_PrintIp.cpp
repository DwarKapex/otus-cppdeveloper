/**
 * \brief Unit tests for PrintIp library
 *
 */

#define BOOST_TEST_MODULE PrintIp_TESTS

#include <boost/test/unit_test.hpp>
#include <PrintIp/PrintIp.h>
#include <vector>
#include <tuple>
#include <list>
#include <string>

using namespace PrintIp;

BOOST_AUTO_TEST_CASE (print_ip_integral_types)
{
    char ip_char{-1};
    BOOST_CHECK_MESSAGE(print_ip(ip_char) == "255", "char [-1]");
    
    ip_char = 18;
    BOOST_CHECK_MESSAGE(print_ip(ip_char) == "18", "char [18]");

    uint8_t ip_uint8{27};
    std::string expected_value = "27";
    BOOST_CHECK_MESSAGE(print_ip(ip_uint8) == expected_value, "uint8 [27]");

    int16_t ip_int16{-1111};
    expected_value = "251.169";
    BOOST_CHECK_MESSAGE(print_ip(ip_int16) == expected_value, "int16 [-1111]");

    int32_t ip_int32{-111111111};
    expected_value = "249.96.148.57";
    BOOST_CHECK_MESSAGE(print_ip(ip_int32) == expected_value, "int32 [-111111111]");
    
    uint64_t ip_int64{1111111111111111111};
    expected_value = "15.107.117.171.43.196.113.199";
    BOOST_CHECK_MESSAGE(print_ip(ip_int64) == expected_value, "int64 [1111111111111111111]");
 }

BOOST_AUTO_TEST_CASE(print_ip_container_test) {
  std::vector<uint8_t> ip_vec1{1, 2, 3, 4};
  std::string expected_value{"1.2.3.4"};
  BOOST_CHECK_MESSAGE(print_ip(ip_vec1) == expected_value, "vector{1, 2, 3, 4}");

  std::vector<uint16_t> ip_vec2{111, 222, 333, 444};
  expected_value = "111.222.333.444";
  BOOST_CHECK_MESSAGE(print_ip(ip_vec2) == expected_value, "vector{111, 222, 333, 444}");
  
  std::list<uint8_t> ip_list1{1, 2, 3, 4};
  expected_value = "1.2.3.4";
  BOOST_CHECK_MESSAGE(print_ip(ip_list1) == expected_value, "list{1, 2, 3, 4}");

  std::list<uint32_t> ip_list2{111, 222, 333, 444};
  expected_value = "111.222.333.444";
  BOOST_CHECK_MESSAGE(print_ip(ip_list2) == expected_value, "list{111, 222, 333, 444}");
}

BOOST_AUTO_TEST_CASE(print_ip_tuple_test) {
  std::tuple ip_tuple{1, 2, 4, 8};
    std::string expected_value{"1.2.4.8"};
  BOOST_CHECK_MESSAGE(print_ip(ip_tuple) == expected_value, "tuple{1, 2, 4, 8}");
}

BOOST_AUTO_TEST_CASE(print_ip_string) {
  using namespace std::string_literals;
  std::string ip_string("1.2.3.4");
  BOOST_CHECK_MESSAGE(print_ip(ip_string) == "1.2.3.4", "string{1.2.3.4}");

  BOOST_CHECK_MESSAGE(print_ip("1.2.3.4.5.6"s) == "1.2.3.4.5.6", "string{1.2.3.4.5.6}");
}

