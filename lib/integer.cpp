#include "integer.h"

#include <regex>
#include <string>

#include "utils.h"

std::expected<int, std::string> lib::extractInt(const std::string& buffer,
                                                const int& minValue,
                                                const int& maxValue) {
    if (buffer.empty()) {
        return std::unexpected("Empty input data");
    }

    // Dùng regex + stoi theo yêu cầu
    static const std::regex INT_PATTERN(R"(^\s*([+-]?\d+)\s*$)");
    std::smatch match;
    // Một số triển khai regex_match không chấp nhận string_view trực tiếp,
    if (std::regex_match(buffer, match, INT_PATTERN)) {
        try {
            // match.str(1) rõ ràng lấy nhóm con chứa chữ số
            int res = std::stoi(match.str(1));
            if (res < minValue || res > maxValue) {
                return std::unexpected(std::format(
                    "Number out of range, please enter integer that is between {} and {}",
                    minValue,
                    maxValue));
            }
            return res;
        } catch (const std::invalid_argument&) {
            // Về nguyên tắc, nếu regex đã khớp thì không vào đây,
            // nhưng vẫn bắt để an toàn.
            return std::unexpected("Invalid input");
        } catch (const std::out_of_range&) {
            return std::unexpected(
                std::format("Number out of range, please enter integer that is between {} and {}",
                            minValue,
                            maxValue));
        }
    }

    return std::unexpected("Wrong input format");
}

std::expected<int, std::string> lib::getInt(const std::string& message,
                                            const int& minValue,
                                            const int& maxValue) {
    lib::salute(message);

    std::string buffer;
    std::getline(std::cin, buffer);

    // Trả trực tiếp expected từ extractInt để giữ nguyên thông tin lỗi (nếu có)
    return lib::extractInt(buffer, minValue, maxValue);
}
