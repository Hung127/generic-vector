#ifndef _LIB_FLOAT_H_
#define _LIB_FLOAT_H_

#include <expected>
#include <format>
#include <limits>
#include <string>

namespace lib {

/**
 * @brief Phân tích chuỗi thành số thực (có kiểm tra khoảng).
 *
 * Hàm sẽ trim khoảng trắng đầu/cuối, sau đó kiểm tra định dạng bằng regex
 * (theo yêu cầu) và sử dụng std::stof để chuyển sang float. Nếu chuỗi rỗng
 * trả về unexpected("Empty input data"), nếu định dạng sai trả về
 * unexpected("Wrong input format"), nếu vượt khoảng trả về unexpected với
 * thông báo phạm vi.
 *
 * Lưu ý: mặc định minValue và maxValue được đặt thành numeric_limits<float>::lowest()
 * và numeric_limits<float>::max() (lowest() là giá trị âm lớn nhất có thể).
 *
 * @param buffer Chuỗi đầu vào (có thể chứa khoảng trắng).
 * @param minValue Giá trị nhỏ nhất hợp lệ (mặc định numeric_limits<float>::lowest()).
 * @param maxValue Giá trị lớn nhất hợp lệ (mặc định numeric_limits<float>::max()).
 * @return std::expected<float, std::string>
 */
std::expected<float, std::string> extractFloat(
    const std::string& buffer,
    const float& minValue = std::numeric_limits<float>::lowest(),
    const float& maxValue = std::numeric_limits<float>::max());

/**
 * @brief Đọc một dòng từ stdin và parse thành float (gọi extractFloat).
 *
 * Hàm sẽ in message (bằng lib::salute), đọc một dòng từ stdin và gọi extractFloat.
 *
 * @param message Thông báo/nhắc người dùng.
 * @param minValue Giá trị nhỏ nhất hợp lệ.
 * @param maxValue Giá trị lớn nhất hợp lệ.
 * @return std::expected<float, std::string>
 */
std::expected<float, std::string> getFloat(
    const std::string& message,
    const float& minValue = std::numeric_limits<float>::lowest(),
    const float& maxValue = std::numeric_limits<float>::max());

}  // namespace lib

#endif  // !_LIB_FLOAT_H_
