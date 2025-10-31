#include "Student.h"

#include <format>

using std::format;
using std::string;

const string Student::DEFAULT_ID;
const string Student::DEFAULT_NAME;
const float Student::DEFAULT_GPA = -1.0F;

// Constructor
Student::Student(const string& id, const string& name, float gpa) :
    _id(id),
    _fullname(name),
    _gpa(gpa) {}

// Constructor
Student::Student() :
    _id(DEFAULT_ID),
    _fullname(DEFAULT_NAME),
    _gpa(DEFAULT_GPA) {}

float Student::getGPA() const { return _gpa; }
string Student::getID() const { return _id; }
string Student::getFullname() const { return _fullname; }

std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << format(
        "ID: {} - Fullname: {} - GPA: {}",
        student.getID(),
        student.getFullname(),
        student.getGPA());
    return os;
}

bool operator<(const Student& student1, const Student& student2) {
    return (student1.getGPA() < student2.getGPA());
}
