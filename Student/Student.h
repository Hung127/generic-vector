#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <expected>
#include <iostream>
#include <ostream>
#include <string>

/**
 * @file Student.h
 * @brief Định nghĩa kiểu dữ liệu Student và các toán tử liên quan.
 *
 * Lưu ý: lớp Student cung cấp phương thức tĩnh getStudent để đọc thông tin
 * sinh viên từ stdin (sử dụng lib::getValueRetry/lib::getFloat).
 */

class Student {
private:
    std::string _id;       /**< Mã sinh viên */
    std::string _fullname; /**< Họ tên sinh viên */
    float _gpa;            /**< Điểm trung bình (GPA) */

public:
    /** Giá trị mặc định cho id (chuỗi rỗng) */
    static const std::string DEFAULT_ID;
    /** Giá trị mặc định cho tên (chuỗi rỗng) */
    static const std::string DEFAULT_NAME;
    /** Giá trị mặc định cho GPA (sử dụng -1.0F để nhận biết chưa khởi tạo) */
    static const float DEFAULT_GPA;

    /**
     * @brief Lấy mã sinh viên.
     * @return std::string Mã sinh viên (readonly).
     */
    [[nodiscard]] std::string getID() const;

    /**
     * @brief Lấy họ tên sinh viên.
     * @return std::string Họ tên (readonly).
     */
    [[nodiscard]] std::string getFullname() const;

    /**
     * @brief Lấy GPA của sinh viên.
     * @return float Giá trị GPA (readonly).
     */
    [[nodiscard]] float getGPA() const;

    /**
     * @brief Đọc thông tin sinh viên từ người dùng.
     *
     * Hàm sẽ hiển thị message (bằng lib::salute), sau đó yêu cầu nhập id,
     * họ tên và gpa. Hàm sử dụng lib::getValueRetry + lib::getFloat để đọc
     * GPA với giới hạn minGPA/maxGPA và số lần thử giới hạn (xem cài đặt).
     *
     * @param message Thông báo/giới thiệu chương trình cho người dùng.
     * @param minGPA Giá trị nhỏ nhất hợp lệ cho GPA.
     * @param maxGPA Giá trị lớn nhất hợp lệ cho GPA.
     * @return std::expected<Student, std::string> Trả Student khi thành công,
     *         hoặc unexpected với mô tả lỗi khi thất bại.
     */
    static std::expected<Student, std::string> getStudent(const std::string& message,
                                                          const float& minGPA,
                                                          const float& maxGPA);

    /**
     * @brief Constructor.
     * @param id Mã sinh viên.
     * @param name Họ tên.
     * @param gpa Điểm trung bình.
     */
    Student(const std::string& id, const std::string& name, float gpa);

    /**
     * @brief Constructor mặc định.
     *
     * Khởi tạo với DEFAULT_ID, DEFAULT_NAME, DEFAULT_GPA.
     */
    Student();
};

/**
 * @brief Ghi Student ra luồng ostream.
 *
 * Định dạng: "ID: <id> - Fullname: <fullname> - GPA: <gpa>"
 */
std::ostream& operator<<(std::ostream& os, const Student& student);

/**
 * @brief So sánh hai Student theo GPA.
 * @return true nếu student1.gpa < student2.gpa
 */
bool operator<(const Student& student1, const Student& student2);

/**
 * @brief So sánh Student với một số float (gpa).
 * @return true nếu student1.gpa < floatnum
 */
bool operator<(const Student& student1, const float& floatnum);

#endif  // !_STUDENT_H_
