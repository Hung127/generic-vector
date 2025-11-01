#include "floatnum.h"

#include <regex>
#include <string>

#include "utils.h"

std::expected<float, std::string> lib::extractFloat(const std::string& buffer,
                                                    const float& minValue,
                                                    const float& maxValue) {
    if (buffer.empty()) {
        return std::unexpected("Empty input data");
    }

    static const std::regex INT_PATTERN(R"(^\s*[+-]?\d+\s*$)");
    static const std::regex FLOAT_PATTERN(R"(^\s*[+-]?\d+\.\d+\s*$)");

    if (std::regex_match(buffer, FLOAT_PATTERN) || std::regex_match(buffer, INT_PATTERN)) {
        try {
            float res = std::stof(buffer);
            if (res < minValue || res > maxValue) {
                return std::unexpected(
                    std::format("Number out of range, please enter float that is between {} and {}",
                                minValue,
                                maxValue));
            }
            return res;
        } catch (const std::invalid_argument&) {
            // Thực tế nếu regex_match khớp thì ít khi vào đây, nhưng giữ an toàn
            return std::unexpected("Invalid input");
        } catch (const std::out_of_range&) {
            return std::unexpected(
                std::format("Number out of range, please enter float that is between {} and {}",
                            minValue,
                            maxValue));
        }
    }

    return std::unexpected("Wrong input format");
}

std::expected<float, std::string> lib::getFloat(const std::string& message,
                                                const float& minValue,
                                                const float& maxValue) {
    lib::salute(message);

    std::string buffer;
    std::getline(std::cin, buffer);

    // Trả trực tiếp expected từ extractFloat để bảo toàn thông tin lỗi (nếu có)
    return lib::extractFloat(buffer, minValue, maxValue);
}
