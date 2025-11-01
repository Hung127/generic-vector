#ifndef _LIB_VECTOR_H_
#define _LIB_VECTOR_H_

#include <expected>
#include <iostream>
#include <string>

namespace lib {

/**
 * @brief Mảng động tối giản (dynamic array).
 *
 * Lớp này cung cấp một container động đơn giản với API tối giản:
 *  - push_back để thêm phần tử ở cuối
 *  - size/capacity/data để truy vấn trạng thái bộ nhớ
 *  - operator[] trả std::expected<T,std::string> cho truy xuất có kiểm tra biên
 *
 * Lưu ý:
 *  - Thiết kế hiện sử dụng cấp phát thủ công (new[] / delete[]).
 *  - Không có move constructor/assignment và không có guarantee ngoại lệ mạnh.
 *  - Phù hợp cho mục đích học tập / ví dụ; cân nhắc dùng std::vector hoặc cải tiến
 *    để dùng std::unique_ptr/T allocator cho mã thực tế.
 *
 * @tparam T Kiểu phần tử lưu trong vector.
 */
template <class T>
class vector {
private:
    T* _arr;                           /**< Con trỏ tới mảng phần tử nội bộ (owned) */
    int _capacity;                     /**< Dung lượng hiện tại (số phần tử tối đa có thể chứa) */
    int _size;                         /**< Số phần tử thực tế đang lưu (0.._capacity) */
    static const int EXPAND_TIMES = 2; /**< Hệ số nhân khi mở rộng */

public:
    // constructors / destructor

    /**
     * @brief Khởi tạo mặc định, tạo mảng với capacity = 1.
     *
     * Complexities: O(1) (cấp phát bộ nhớ).
     */
    vector();

    /**
     * @brief Khởi tạo với dung lượng ban đầu.
     *
     * Nếu capacity <= 0 sẽ sử dụng 1.
     *
     * @param capacity Dung lượng khởi tạo mong muốn.
     */
    explicit vector(int capacity);

    /**
     * @brief Hủy và giải phóng bộ nhớ nội bộ.
     */
    ~vector();

    // modifiers / observers

    /**
     * @brief Thêm một phần tử vào cuối vector.
     *
     * Nếu _size == _capacity, hàm sẽ cấp phát một mảng lớn hơn (nhân EXPAND_TIMES),
     * sao chép dữ liệu cũ sang mảng mới rồi xóa mảng cũ.
     *
     * Complexity: Amortized O(1). Có thể ném ngoại lệ nếu T copy ctor ném hoặc new ném.
     *
     * @param value Phần tử cần thêm (tham chiếu const).
     */
    void push_back(const T& value);  // NOLINT

    /**
     * @brief Trả về số phần tử hiện có trong vector.
     *
     * @return int Số phần tử hiện tại.
     */
    [[nodiscard]] int size() const;

    // additional helpers

    /**
     * @brief Trả về dung lượng hiện tại của mảng nội bộ.
     *
     * @return int Dung lượng (capacity).
     */
    [[nodiscard]] int capacity() const;

    /**
     * @brief Trả về con trỏ tới mảng nội bộ (có thể dùng để truy xuất nhanh).
     *
     * Lưu ý: con trỏ trở nên không hợp lệ sau khi push_back làm reallocation.
     *
     * @return T* Con trỏ tới dữ liệu (mutable).
     */
    T* data();

    // bounds-checked read operator returning an expected

    /**
     * @brief Truy xuất phần tử theo chỉ số với kiểm tra biên.
     *
     * Nếu idx nằm ngoài [0, size()), trả về unexpected("Out of range").
     * Ngược lại trả về bản sao của phần tử tại vị trí idx (đóng gói bởi expected).
     *
     * Complexity: O(1).
     *
     * @param idx Chỉ số (int). Nếu idx < 0 hoặc idx >= size() => out of range.
     * @return std::expected<T, std::string> Giá trị hoặc lỗi.
     */
    std::expected<T, std::string> operator[](int idx) const;
};

// ---------------- Implementation ----------------

// Default ctor
template <class T>
lib::vector<T>::vector() : _arr(new T[1]), _capacity(1), _size(0) {}

// Constructor with initial capacity (if capacity <= 0, use 1)
template <class T>
lib::vector<T>::vector(int capacity)
    : _arr(new T[(capacity > 0) ? capacity : 1]),
      _capacity(capacity > 0 ? capacity : 1),
      _size(0) {}

// Destructor
template <class T>
lib::vector<T>::~vector() {
    delete[] _arr;
}

// push_back (reallocates when necessary)
template <class T>
void lib::vector<T>::push_back(const T& value) {
    if (_size == _capacity) {
        // allocate larger buffer first
        int newCap = (_capacity == 0) ? 1 : _capacity * EXPAND_TIMES;
        T* newArr = new T[newCap];
        std::copy(_arr, _arr + _size, newArr);
        delete[] _arr;
        _arr = newArr;
        _capacity = newCap;
    }
    _arr[_size] = value;  // may throw if T copy ctor throws
    ++_size;
}

template <class T>
int lib::vector<T>::size() const {
    return _size;
}

template <class T>
int lib::vector<T>::capacity() const {
    return _capacity;
}

template <class T>
T* lib::vector<T>::data() {
    return _arr;
}

// bounds-checked operator[]
template <class T>
std::expected<T, std::string> lib::vector<T>::operator[](int idx) const {
    if ((idx < 0) || (idx >= _size)) {
        return std::unexpected<std::string>("Out of range");
    }
    return _arr[idx];
}

}  // namespace lib

#endif  // !_LIB_VECTOR_H_
