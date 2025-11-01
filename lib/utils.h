#ifndef _LIB_UTILS_H_
#define _LIB_UTILS_H_

#include <expected>
#include <format>
#include <iostream>
#include <sstream>
#include <string>

#include "../vector/vector.h"

namespace lib {

/**
 * @brief Hàm toán tử dùng bởi accumulate.
 *
 * Kiểu này biểu diễn một hàm nhận (current_result, next_value) và trả về
 * std::expected<T, std::string>. Nếu thao tác thành công trả về giá trị T,
 * nếu lỗi trả về unexpected với mô tả lỗi.
 *
 * @tparam T Kiểu phần tử.
 */
template <class T>
using Operator = std::expected<T, std::string> (*)(const T&, const T&);

/**
 * @brief Kiểu con trỏ hàm đọc giá trị có giới hạn.
 *
 * Hàm đọc sẽ nhận vào:
 *  - prompt message (const std::string&)
 *  - min value (const MaxMinT&)
 *  - max value (const MaxMinT&)
 *
 * and trả về std::expected<T, std::string> (giá trị hoặc lỗi).
 *
 * Lưu ý: số lần thử (maxAttempts) được quản lý bởi getValueRetry, không phải
 * bởi hàm reader này.
 *
 * @tparam T Kiểu giá trị trả về.
 * @tparam MaxMinT Kiểu dùng để biểu diễn min/max (ví dụ int hoặc float).
 */
template <class T, class MaxMinT>
using BoundedInputReaderFn = std::expected<T, std::string> (*)(const std::string&,
                                                               const MaxMinT&,
                                                               const MaxMinT&);

/**
 * @brief Kiểu điều kiện (nếu cần).
 *
 * Hàm nhận const T& và trả về bool.
 *
 * @tparam T Kiểu đối tượng.
 */
template <class T>
using Condition = bool (*)(const T&);

/**
 * @brief Thử đọc một giá trị bằng getInput tối đa maxAttempts lần.
 *
 * Hàm sẽ gọi getInput(message, minValue, maxValue) lặp lại cho đến khi nhận được
 * giá trị hợp lệ hoặc vượt quá số lần thử. Mỗi lần getInput trả về unexpected,
 * hàm sẽ in thông báo lỗi (sử dụng lib::salute) và yêu cầu thử lại cho đến hết
 * số lần. Nếu thành công trả về expected chứa giá trị, nếu hết lượt trả về
 * unexpected với mô tả lỗi cuối cùng.
 *
 * @tparam T Kiểu giá trị muốn đọc.
 * @tparam MaxMinT Kiểu cho min/max.
 * @param message Thông báo/nhắc nhập.
 * @param minValue Giá trị nhỏ nhất hợp lệ.
 * @param maxValue Giá trị lớn nhất hợp lệ.
 * @param getInput Hàm đọc giá trị (BoundedInputReaderFn).
 * @param maxAttempts Số lần thử tối đa (mặc định 5).
 * @return std::expected<T, std::string>
 */
template <class T, class MaxMinT>
std::expected<T, std::string> getValueRetry(const std::string& message,
                                            const MaxMinT& minValue,
                                            const MaxMinT& maxValue,
                                            BoundedInputReaderFn<T, MaxMinT> getInput,
                                            int maxAttempts = 5);

/**
 * @brief Gom (accumulate) các phần tử trong lib::vector<T> bằng toán tử op.
 *
 * Duyệt qua các phần tử v; với mỗi phần tử có value (expected::has_value()),
 * gọi op(current_result, element). Nếu op trả về unexpected thì lỗi sẽ được
 * propagate ngay lập tức (hàm trả về unexpected). Nếu op thành công thì cập
 * nhật result.
 *
 * @tparam T Kiểu phần tử.
 * @param v vector chứa các expected<T, string> hoặc giá trị tương tự.
 * @param init Giá trị khởi tạo cho phép cộng dồn.
 * @param op Hàm toán tử kiểu lib::Operator<T>.
 * @return std::expected<T, std::string> Giá trị tích lũy hoặc lỗi.
 */
template <class T>
std::expected<T, std::string> accumulate(const lib::vector<T>& v, const T& init, Operator<T> op);

/**
 * @brief Chuyển một giá trị có thể in ra string bằng ostream sang std::string.
 *
 * Hiện trả về std::expected<std::string, std::string> để tương thích với các
 * phần còn lại trong mã, mặc dù thực tế không có trường hợp lỗi. Có thể cân
 * nhắc đổi về plain std::string trong tương lai.
 *
 * @tparam T Kiểu giá trị (cần hỗ trợ operator<<).
 * @param value Giá trị cần chuyển.
 * @return std::expected<std::string, std::string>
 */
template <class T>
std::expected<std::string, std::string> getString(const T& value);

/**
 * @brief In lời chào / thông báo (giao diện người dùng).
 *
 * Thực thi cụ thể ở utils.cpp.
 *
 * @param s Chuỗi cần in.
 */
void salute(const std::string& s);

/**
 * @brief Thông báo thoát chương trình / kết thúc.
 *
 * Thực thi cụ thể ở utils.cpp.
 */
void bye();

}  // namespace lib

// ------------------------ Implementations (template) ------------------------

template <class T>
std::expected<T, std::string> lib::accumulate(const lib::vector<T>& v,
                                              const T& init,
                                              lib::Operator<T> op) {
    T result = init;
    const int len = static_cast<int>(v.size());
    for (int i = 0; i < len; ++i) {
        if (v[i].has_value()) {
            auto resultPack = op(result, v[i].value());
            if (!resultPack.has_value()) {
                // Khi toán tử gặp lỗi, trả về ngay lỗi đó để người gọi xử lý.
                return std::unexpected(resultPack.error());
            }
            result = resultPack.value();
        }
    }
    return result;
}

template <class T, class MaxMinT>
std::expected<T, std::string> lib::getValueRetry(const std::string& message,
                                                 const MaxMinT& minValue,
                                                 const MaxMinT& maxValue,
                                                 lib::BoundedInputReaderFn<T, MaxMinT> getInput,
                                                 int maxAttempts) {
    int failedCounts = 0;

    while (failedCounts < maxAttempts) {
        auto result = getInput(message, minValue, maxValue);

        if (!result.has_value()) {
            ++failedCounts;
            // Hiện vẫn hiển thị thông báo lỗi tại chỗ; nếu muốn test dễ hơn,
            // có thể tách logging ra callback sau.
            lib::salute(std::format("Error: {}\n", result.error()));
            if (failedCounts < maxAttempts) {
                std::cout << "You have " << (maxAttempts - failedCounts)
                          << " attempts left. Please try again.\n";
            }
        } else {
            return result;  // trả về giá trị thành công
        }
    }

    return std::unexpected(std::format("Exceeded the max attempts: {}", maxAttempts));
}

template <class T>
std::expected<std::string, std::string> lib::getString(const T& value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

#endif  // !_LIB_UTILS_H_
