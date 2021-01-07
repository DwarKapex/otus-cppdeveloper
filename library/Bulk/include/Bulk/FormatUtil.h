#pragma once

#include <vector>
#include <string>

namespace bulk::FormatUtil {

auto Format(const std::vector<std::string>&, const std::string& delimiter) -> std::string;
auto StripString(std::string&) -> void;

} // namespace bulk::FormatUtil
