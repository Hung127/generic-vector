#include "Student.h"

#include <format>
#include <sstream>

#include "../lib/floatnum.h"
#include "../lib/utils.h"

using std::format;
using std::ostringstream;
using std::string;

const string Student::DEFAULT_ID;
const string Student::DEFAULT_NAME;
const float Student::DEFAULT_GPA = -1.0F;

// Constructor
Student::Student(const string& id, const string& name, float gpa)
    : _id(id), _fullname(name), _gpa(gpa) {}

// Constructor
Student::Student() : _id(DEFAULT_ID), _fullname(DEFAULT_NAME), _gpa(DEFAULT_GPA) {}

float Student::getGPA() const { return _gpa; }
string Student::getID() const { return _id; }
string Student::getFullname() const { return _fullname; }

expected<Student, string> Student::getStudent(const string& message,
                                              const float& minGPA,
                                              const float& maxGPA) {
    const int GPA_ATTEMPTS = 1;

    lib::salute(message);

    string id;
    lib::salute("Enter id: ");
    getline(cin, id);

    string fullname;
    lib::salute("Enter fullname: ");
    getline(cin, fullname);

    auto gpaPack = lib::getValueRetry("Enter gpa: ", minGPA, maxGPA, lib::getFloat, GPA_ATTEMPTS);
    if (!gpaPack.has_value()) {
        return unexpected(gpaPack.error());
    }

    return Student(id, fullname, gpaPack.value());
}

std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << format("ID: {} - Fullname: {} - GPA: {}",
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
