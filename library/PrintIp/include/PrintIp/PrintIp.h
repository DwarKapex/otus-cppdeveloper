/**
 * \brief PrintIp library header
 */

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <type_traits>


namespace PrintIp {

/// Some bulshit to teset doxygen
template<typename T>
std::enable_if_t<std::is_integral<T>::value, std::string> print_ip_impl(const T& value) {
    size_t type_size = sizeof(T);
    std::string result;
    for (size_t i = type_size; i > 0 ; --i) {
        result += std::to_string((value >> (8*(i-1)) & 0xFF))
            + (i != 1 ? "." : "");
    }
    return result;
}

/*

use std::is_same_v<> for simplicity

// template<typename T>
// struct is_string : std::false_type {};
// template<>
// struct is_string<std::string>: std::true_type {};
// template<typename T>
// inline constexpr bool is_string_t = is_string<T>::value;
*/

/**
  * \brief Convert input value (of std::string) to string
  * \tparam T template paramter as a string
  * \param[in]  value ip address to print
  * \param[out] string with result
*/
template<typename T>
std::enable_if_t<std::is_same<std::decay_t<T>, std::string>::value, std::string> 
    print_ip_impl(const T& value) {
    return value;
}

template<typename T>
struct is_container: std::false_type {};
template<typename ...T>
struct is_container<std::vector<T...>>: std::true_type {};
template<typename ...T>
struct is_container<std::list<T...>>: std::true_type {};
template<typename U>
inline constexpr bool is_container_v = is_container<U>::value;

/**
  * \brief Convert input value (of STL containers (std::vector, std::list for now)) to string
  * \tparam T template paramter such as a std::vector, std::list
  * \param[in]  value ip address to print
  * \param[out] string with result
*/
template<typename T>
std::enable_if_t<is_container_v<T>, std::string> print_ip_impl(const T& value){
    std::string result;
    for (const auto& item: value)
        result += std::to_string(item) + '.';
    result.pop_back();
    return result;
}

// Set of templated structs to check whether tuple has the same types of values
// But there is no check whether all these values are convertable into string =((

/*
There is a std::conjunction_v<> (https://en.cppreference.com/w/cpp/types/conjunction) 
for this

// template <typename T, typename... Args>
// struct is_all_same;
// template <typename T>
// struct is_all_same<T> : public std::true_type {};
// template <typename T, typename U, typename...Args>
// struct is_all_same<T, U, Args...> : public std::false_type {};
// template <typename T, typename...Args>
// struct is_all_same<T, T, Args...> : public is_all_same<T, Args...> {};
// template<typename... T>
// inline constexpr bool is_all_same_v = is_all_same<T...>::value;
*/

template<typename T, size_t pos, size_t size>
struct build_tuple_string {
  static std::string get_tuple_value(const T& value) {
    if constexpr(pos != size) {
      return  std::to_string(std::get<pos>(value)) + '.'+
              build_tuple_string<T, pos + 1, size>::get_tuple_value(value);
    } else {
      return std::to_string(std::get<size>(value));
    }
  }
};

/**
  * \brief Convert input value (of std::tuple) to string
  * \tparam T template paramter such as a std::vector, std::list
  * \param[in]  value ip address in tuple format
  * \param[out] string with result
*/
template <typename T, typename... Tail>
std::enable_if_t<std::conjunction<std::is_same<T, Tail>...>::value, std::string> print_ip_impl(const std::tuple<T, Tail...>& ip) {
  constexpr int num_args_tuple = std::tuple_size<std::tuple<T, Tail...>>::value;
  return build_tuple_string<std::tuple<T, Tail...>, 0, num_args_tuple - 1>::get_tuple_value(ip);
}

/**
  * \brief Decorator for for to-string converters.
  * \tparam T template paramter such of any kind, that can represent the IP address
  * \param[in]  value ip address to print
  * \param[out] string with result
*/
template<typename T>
std::string print_ip(const T& value){
    return print_ip_impl(value);
}
} // namespace PrintIp
