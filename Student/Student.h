#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <iostream>
#include <ostream>
#include <string>

class Student {
private:
    std::string _id;
    std::string _fullname;
    float _gpa;

public:
    static const std::string DEFAULT_ID;
    static const std::string DEFAULT_NAME;
    static const float DEFAULT_GPA;

    [[nodiscard]] std::string getID() const;
    [[nodiscard]] std::string getFullname() const;
    [[nodiscard]] float getGPA() const;

    // Constructor
    Student(const std::string& id, const std::string& name, float gpa);

    // Constructor
    Student();
};

std::ostream& operator<<(std::ostream& os, const Student& student);
bool operator<(const Student& student1, const Student& student2);

#endif  // !_STUDENT_H_
