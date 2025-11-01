#include "integer.h"

#include "utils.h"

expected<int, string> lib::extractInt(const string& buffer,
                                      const int& minValue,
                                      const int& maxValue) {
    static const regex INT_PATTERN(R"(^([+-]?\d+)$)");
    smatch match;
    if (buffer.size() == 0) {
        return unexpected("Empty input data");
    }
    if (regex_match(buffer, match, INT_PATTERN)) {
        try {
            int res = std::stoi(match[1]);
            if ((res < minValue) || (res > maxValue)) {
                return unexpected(
                    format("Number out of range, please enter integer that is between {} and {}",
                           minValue,
                           maxValue));
            }
            return res;
        } catch (const std::invalid_argument& e) {
            return unexpected("Invaid input");
        } catch (const std::out_of_range& e) {
            return unexpected(
                format("Number out of range, please enter integer that is between {} and {}",
                       minValue,
                       maxValue));
        }
    }
    return unexpected("Wrong input format");
}

expected<int, string> lib::getInt(const string& message, const int& minValue, const int& maxValue) {
    lib::salute(message);

    string buffer;
    getline(cin, buffer);

    auto result = lib::extractInt(buffer, minValue, maxValue);

    if (!result.has_value()) {
        return unexpected(result.error());
    }
    return result.value();
}
