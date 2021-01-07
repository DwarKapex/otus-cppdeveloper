
#include <Bulk/FormatUtil.h>

#include <string>
#include <algorithm>
#include <vector>
#include <numeric>

namespace bulk::FormatUtil {

void StripString(std::string& s){
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            [](char ch){ return !std::isspace(ch);
    }));
    s.erase(std::find_if(s.rbegin(), s.rend(),
            [](char ch){ return !std::isspace(ch);
    }).base(), s.end());
}

auto Format(const std::vector<std::string>& value, const std::string& delimiter) -> std::string {
    std::string result;
    if (!value.empty()) {    
        const size_t result_size = std::accumulate(value.begin(), value.end(), 0,
        [](size_t init, const std::string& s) { return init + s.size() + 2;}
        );
        result.reserve(result_size-2);
        // append first element
        result += value.front();
        for (auto it = std::next(value.begin()); it != value.end(); ++it) {
            result+= delimiter + *it;
        }
    }

    return result;
}

} //namespace bulk::FormatUtil
