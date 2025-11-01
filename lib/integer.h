#ifndef _LIB_INTEGER_H_
#define _LIB_INTEGER_H_

#include <climits>
#include <expected>
#include <format>
#include <string>

namespace lib {

/**
 * @brief Chuyển chuỗi thành số nguyên (có kiểm tra khoảng).
 *
 * Hàm phân tích buffer (sẽ loại bỏ khoảng trắng đầu/cuối trước khi phân tích),
 * nếu buffer rỗng trả về unexpected("Empty input data"), nếu định dạng không hợp lệ
 * trả về unexpected("Wrong input format"), nếu số nằm ngoài [minValue, maxValue]
 * trả về unexpected với thông báo phạm vi.
 *
 * Lưu ý: phiên bản này sử dụng regex + std::stoi theo yêu cầu.
 *
 * @param buffer Chuỗi đầu vào (có thể chứa khoảng trắng).
 * @param minValue Giá trị nhỏ nhất hợp lệ (mặc định INT_MIN).
 * @param maxValue Giá trị lớn nhất hợp lệ (mặc định INT_MAX).
 * @return std::expected<int, std::string>
 */
std::expected<int, std::string> extractInt(const std::string& buffer,
                                           const int& minValue = INT_MIN,
                                           const int& maxValue = INT_MAX);

/**
 * @brief Đọc một dòng từ stdin và parse thành int (gọi extractInt).
 *
 * Hàm sẽ in message (bằng lib::salute), đọc một dòng từ stdin và gọi extractInt.
 *
 * @param message Thông báo/nhắc người dùng.
 * @param minValue Giá trị nhỏ nhất hợp lệ.
 * @param maxValue Giá trị lớn nhất hợp lệ.
 * @return std::expected<int, std::string>
 */
std::expected<int, std::string> getInt(const std::string& message,
                                       const int& minValue = INT_MIN,
                                       const int& maxValue = INT_MAX);

}  // namespace lib

#endif  // !_LIB_INTEGER_H_
