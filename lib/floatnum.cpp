#include "floatnum.h"

#include <expected>
#include <regex>
#include <string>

#include "integer.h"

using std::expected, std::unexpected;
using std::regex, std::regex_match, std::smatch;
using std::string;

expected<float, string> lib::extractFloat(const string& buffer, const float& minValue,
                                          const float& maxValue) {
    const regex INT_PATTERN(R"(^([+-]?\d+)$)");
    const regex FLOAT_PATTERN(R"(^([+-]?\d+\.\d+)$)");

    if (buffer.size() == 0) {
        return unexpected("Empty input data");
    }

    if ((regex_match(buffer, FLOAT_PATTERN)) || (regex_match(buffer, INT_PATTERN))) {
        try {
            float res = std::stof(buffer);
            if ((res < minValue) || (res > maxValue)) {
                return unexpected(
                    format("Number out of range, please enter integer that is between {} and {}",
                           minValue, maxValue));
            }
            return res;
        } catch (const std::invalid_argument& e) {
            return unexpected("Invaid input");
        } catch (const std::out_of_range& e) {
            return unexpected(
                format("Number out of range, please enter float that is between {} and {}",
                       minValue, maxValue));
        }
    }
    return unexpected("Wrong input format");
}
