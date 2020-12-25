#include <Allocator/Allocator.h>
#include <Allocator/List.h>

#include <iostream>
#include <map>


int main() {
    size_t factorial = 1;

    // map with std::allocator
    std::map<int, int> std_m;
    for (size_t i = 0; i < 10; ++i) {
        std_m[i] = factorial;
        factorial *= (i+1);
    }
    for (auto it = std_m.begin(); it != std_m.end(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }

    // map with custom allocator
    factorial = 1;
    std::map<int, int, std::less<int>, 
            Allocator::Allocator<std::pair<const int, int>, 10>> m;
    for (size_t i = 0; i < 10; ++i) {
        m[i] = factorial;
        factorial *= (i+1);
    }
    for (auto it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }

    // custom container with std::allocator
    Allocator::List<int> std_l;
    for (int i = 0; i < 10; ++i) {
        std_l.push_back(i);
    }
    for (auto it = std_l.begin(); it != std_l.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // custom container with custom allocator
    Allocator::List<int, Allocator::Allocator<int, 11>> l;
    for (int i = 0; i < 10; ++i) {
        l.push_back(i);
    }
    for (auto it = l.begin(); it != l.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;



    return 0;
}
