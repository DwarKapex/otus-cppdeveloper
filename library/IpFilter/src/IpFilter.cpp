#include <IpFilter/IpFilter.h>

#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <limits>

namespace IpFilter{


//------------------------------------------------------------------
#pragma mark IpAddress Implementation
//------------------------------------------------------------------
namespace detail{

bool lexical_compare_less(const IpAddress::value_type lhs, const IpAddress::value_type rhs) {
    return std::to_string(lhs) < std::to_string(rhs);
}

} // namespace detal

std::ostream& operator<<(std::ostream& os, const IpAddress& ip) {
    assert(ip.size() == 4u);
    std::copy(ip.begin(), ip.end()-1, std::ostream_iterator<IpAddress::value_type>(os, "."));
    os << ip.back();
    return os;
}

std::istream& operator>>(std::istream& is, IpAddress& ip) {
    constexpr size_t kIpAddressSize=4u;
    char delimiter='.';
    for(size_t idx=0; idx < kIpAddressSize; ++idx){
        std::string byte;
        std::getline(is, byte, delimiter);
        IpAddress::value_type val=std::stoi(byte);
        if(val < 0 || val>255) {
            throw std::out_of_range("IP address bytes must be in range [0:255]");
        }
        ip.push_back(val);
        if (idx==2) {
            delimiter='\t';
        }
    }
    return is;
}

bool operator<(const IpAddress& lhs, const IpAddress& rhs) {
    assert(lhs.size()==4u);
    assert(rhs.size()==4u);
    return std::lexicographical_compare(lhs.begin(), lhs.end(), 
                                        rhs.begin(), rhs.end(), 
                                        detail::lexical_compare_less);
}

bool operator>(const IpAddress& lhs, const IpAddress& rhs) {
    return !(lhs<rhs);
}

//------------------------------------------------------------------
#pragma mark IpPool Implementation
//------------------------------------------------------------------
IpPool::IpPool(const IpPool_t& from): m_ip_pool(from) {}
IpPool::IpPool() = default;

auto IpPool::begin()->decltype(m_ip_pool.begin()) { return m_ip_pool.begin();}
auto IpPool::end()->decltype(m_ip_pool.begin()) { return m_ip_pool.end();}

auto IpPool::begin() const ->const decltype(m_ip_pool.begin()) { return m_ip_pool.begin();}
auto IpPool::end() const ->const decltype(m_ip_pool.begin()) { return m_ip_pool.end();}

void IpPool::push_back(const IpAddress& ip) {
    m_ip_pool.push_back(ip);
}

void IpPool::Sort() {
    std::sort(m_ip_pool.begin(), m_ip_pool.end(), std::greater<IpAddress>());
}

auto IpPool::FilterAny(const size_t byte) -> IpPool_t {
    IpPool_t result;
    std::copy_if(m_ip_pool.begin(), m_ip_pool.end(), std::back_inserter(result),
                         [&byte](const IpAddress& item){
                return std::any_of(item.begin(), item.end(), [&byte](int a){return a == byte;});
            
            });
    return result;
}

std::ostream& operator<<(std::ostream& os, const IpPool& ip_pool) {
    for (const auto& ip_address: ip_pool){
        os << ip_address << std::endl;
    }
    return os;
}

bool operator==(const IpPool& lhs, const IpPool& rhs){
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

std::istream& operator>>(std::istream& is, IpPool& ip_pool) {
    IpAddress temp;
    while (is.peek() != EOF) {
        is >> temp;
        ip_pool.push_back(temp);
        is.ignore(std::numeric_limits<int>::max(), '\n');
        temp.clear();
    }
    return is;
}


} // namespace IpFilter
