#include <vector>
#include <algorithm>
#include <iosfwd>
#include <iterator>

namespace IpFilter{
//------------------------------------------------------------------
#pragma mark IpAddress Declaration
//------------------------------------------------------------------

using IpAddress = std::vector<int>;

namespace detail {
    bool lexical_compare(const IpAddress::value_type lhs, const IpAddress::value_type rhs);
}

std::ostream& operator<<(std::ostream& os, const IpAddress& ip);
std::istream& operator>>(std::istream& os, IpAddress& ip);

bool operator<(const IpAddress& lhs, const IpAddress& rhs);

bool operator>(const IpAddress& lhs, const IpAddress& rhs);

//------------------------------------------------------------------
#pragma mark IpPool Deslcaration
//------------------------------------------------------------------
class IpPool{
public:
    using IpPool_t = std::vector<IpAddress>;
    using value_type = IpPool_t;

    IpPool(const IpPool_t&);
    IpPool();
private:
     IpPool_t m_ip_pool;

public:
    void Sort();

    template <typename ...Args>

    IpPool_t Filter(Args ...args){
        IpAddress lower_mask{args...}, upper_mask{args...};
        ++upper_mask[upper_mask.size()-1];
        lower_mask.resize(4); upper_mask.resize(4);
        auto up =
                std::lower_bound(m_ip_pool.begin(),
                                 m_ip_pool.end(),
                                 lower_mask,
                                 std::greater<IpAddress>());  
         auto low =
                std::lower_bound(m_ip_pool.begin(),
                                 m_ip_pool.end(),
                                 upper_mask,
                                 std::greater<IpAddress>());
        
        IpPool_t result(low, up);
        return result;
    }

    IpPool_t FilterAny(const size_t byte);

    auto begin()->decltype(m_ip_pool.begin());
    auto end()->decltype(m_ip_pool.end());

    auto begin() const ->const decltype(m_ip_pool.begin());
    auto end() const ->const decltype(m_ip_pool.end());
    void push_back(const IpAddress&);
};

std::ostream& operator<<(std::ostream& os, const IpPool& ip_pool);
std::istream& operator>>(std::istream& os, IpPool& ip_pool);
bool operator==(const IpPool& lhs, const IpPool& rhs);
}