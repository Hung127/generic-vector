#ifndef _LIB_FLOAT_H_
#define _LIB_FLOAT_H_

#include <climits>
#include <expected>
#include <format>
#include <iostream>
#include <limits>
#include <regex>
#include <string>

namespace lib {
std::expected<float, std::string> extractFloat(
        const std::string& buffer,
        const float& minValue = std::numeric_limits<float>::min(),
        const float& maxValue = std::numeric_limits<float>::max()
    );
}

#endif  // !_LIB_FLOAT_H_
