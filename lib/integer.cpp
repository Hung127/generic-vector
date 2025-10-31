#include "integer.h"

expected<int, string> lib::extractInt(const string& buffer, const int& minValue,
                                      const int& maxValue) {
    const regex INT_PATTERN(R"(^([+-]?\d+)$)");
    smatch match;
    if (buffer.size() == 0) {
        return unexpected("Empty input data");
    }
    if (regex_match(buffer, match, INT_PATTERN)) {
        try {
            int res = std::stoi(match[1]);
            if (
                (res < minValue)
                || (res > maxValue)
            ) {
                return unexpected(
                    format("Number out of range, please enter integer that is between {} and {}",
                           minValue, maxValue));
            }
            return res;
        } catch (const std::invalid_argument& e) {
            return unexpected("Invaid input");
        } catch (const std::out_of_range& e) {
            return unexpected(
                format("Number out of range, please enter integer that is between {} and {}",
                       minValue, maxValue));
        }
    }
    return unexpected("Wrong input format");
}
