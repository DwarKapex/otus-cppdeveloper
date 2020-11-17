#include <IpFilter/IpFilter.h>
#include <iostream>

using namespace IpFilter;

int main() {
    try {
        IpFilter::IpPool ip_pool;
        std::cin >> ip_pool;
        ip_pool.Sort();
        std::cout << ip_pool;
        std::cout << ip_pool.Filter(1);
        std::cout << ip_pool.Filter(46, 70);
        std::cout << ip_pool.FilterAny(46);        
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
