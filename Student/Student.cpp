#include "Student.h"

#include <format>
#include <sstream>

#include "../lib/floatnum.h"
#include "../lib/utils.h"

// Định nghĩa các hằng số tĩnh (mặc định là chuỗi rỗng / -1.0F)
const std::string Student::DEFAULT_ID;
const std::string Student::DEFAULT_NAME;
const float Student::DEFAULT_GPA = -1.0F;

// Constructor
Student::Student(const std::string& id, const std::string& name, float gpa)
    : _id(id), _fullname(name), _gpa(gpa) {}

// Constructor mặc định
Student::Student() : _id(DEFAULT_ID), _fullname(DEFAULT_NAME), _gpa(DEFAULT_GPA) {}

float Student::getGPA() const { return _gpa; }
std::string Student::getID() const { return _id; }
std::string Student::getFullname() const { return _fullname; }

std::expected<Student, std::string> Student::getStudent(const std::string& message,
                                                        const float& minGPA,
                                                        const float& maxGPA) {
    const int GPA_ATTEMPTS = 1;

    lib::salute(message);

    std::string id;
    lib::salute("Enter id: ");
    std::getline(std::cin, id);

    std::string fullname;
    lib::salute("Enter fullname: ");
    std::getline(std::cin, fullname);

    auto gpaPack = lib::getValueRetry("Enter gpa: ", minGPA, maxGPA, lib::getFloat, GPA_ATTEMPTS);
    if (!gpaPack.has_value()) {
        return std::unexpected(gpaPack.error());
    }

    return Student(id, fullname, gpaPack.value());
}

std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << std::format("ID: {} - Fullname: {} - GPA: {}",
                      student.getID(),
                      student.getFullname(),
                      student.getGPA());
    return os;
}

bool operator<(const Student& student1, const Student& student2) {
    return (student1.getGPA() < student2.getGPA());
}

bool operator<(const Student& student1, const float& floatnum) {
    return (student1.getGPA() < floatnum);
}
