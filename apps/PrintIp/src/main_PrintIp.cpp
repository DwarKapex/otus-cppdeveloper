/**
 * \brief Main application
 */

#include <iostream>
#include <string>
#include <PrintIp/PrintIp.h>

using namespace std::string_literals;

int main() {
    // from arithmetic values
    std::cout << PrintIp::print_ip(static_cast<char>(-1)) << std::endl; // expect 255
    std::cout << PrintIp::print_ip(static_cast<short>(0)) << std::endl; // expect 0.0
    std::cout << PrintIp::print_ip(static_cast<int>(2130706433)) << std::endl;
    std::cout << PrintIp::print_ip(static_cast<long>(8875824491850138409)) << std::endl;
    
    // from string
    std::cout << PrintIp::print_ip(std::string("12.67.89.12")) << std::endl;
    std::cout << PrintIp::print_ip("12.67.89.12"s) << std::endl;
    // from vector
    std::cout << PrintIp::print_ip(std::vector<int>{1,2,3,4,5,6,7}) << std::endl;
    
    // from list
    std::cout << PrintIp::print_ip(std::list<int>{9,8,7,6,5,4,3,2,1}) << std::endl;
 
    // from tuple
    std::cout << PrintIp::print_ip(std::tuple{9,8,7,6,5,4}) << std::endl;
}
