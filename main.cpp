#include "main.h"

#include <format>

#include "./Student/Student.h"
#include "./lib/integer.h"
#include "./lib/utils.h"
#include "./vector/vector.h"

template <class T, class MaxMinT>
void process(const std::string& saluteMsg,
             const std::string& getLenMsg,
             int minLenValue,
             int maxLenValue,
             int maxAttemptsLen,
             const MaxMinT& minValue,
             const MaxMinT& maxValue,
             const std::string& getValueMsg,
             lib::BoundedInputReaderFn<T, MaxMinT> getInputValue,
             int maxAttemptsValue,
             const T& initValue,
             lib::Operator<T> op,
             const std::string& resultMsg);

int main() {
    std::cout << "Exercise 1\n";
    main01();
    std::cout << "---------------------------------------------\n";
    std::cout << "Exercise 2\n";
    main02();
    return 0;
}

void main01() {
    int initValue = 0;
    int minValueArray = 10;
    int maxValueArray = 100;
    int minArrLen = 2;
    int maxArrLen = 5;
    int maxAttemptsLen = 5;
    int maxAttemptsValue = 3;

    process(
        "This is a program that ask you to enter a vector.\nIt will calculate the sum of all "
        "elements that are even in that vector\n",
        "Enter len: ",
        minArrLen,
        maxArrLen,
        maxAttemptsLen,
        minValueArray,
        maxValueArray,
        std::format("Enter integer (between {} and {}): ", minValueArray, maxValueArray),
        lib::getInt,
        maxAttemptsValue,
        initValue,
        // return the sum of a and b if b is even, else, return a
        +[](const int& a, const int& b) -> std::expected<int, std::string> {
            return b % 2 == 0 ? (a + b) : a;
        },
        "The sum of all even elements is: ");
}

void main02() {
    Student initStudent = Student("", "", -1.0F);
    float minGPA = 0.0F;
    float maxGPA = 10.0F;
    int minArrLen = 2;
    int maxArrLen = 5;
    int maxAttemptsLen = 5;
    int maxAttemptsStudent = 2;

    process(
        "This is a program that ask you to enter a vector of student\n The program will find the "
        "student with the highest gpa and print that student to the screen\n",
        "Enter vector length: ",
        minArrLen,
        maxArrLen,
        maxAttemptsLen,
        minGPA,
        maxGPA,
        "",
        Student::getStudent,
        maxAttemptsStudent,
        Student("", "", -1.0F),
        // return the higher gpa one in 2 students
        +[](const Student& a, const Student& b) -> std::expected<Student, std::string> {
            return (a < b ? b : a);
        },
        "The student with highest gpa is: ");
}

template <class T, class MaxMinT>
void process(const std::string& saluteMsg,
             const std::string& getLenMsg,
             int minLenValue,
             int maxLenValue,
             int maxAttemptsLen,
             const MaxMinT& minValue,
             const MaxMinT& maxValue,
             const std::string& getValueMsg,
             lib::BoundedInputReaderFn<T, MaxMinT> getInputValue,
             int maxAttemptsValue,
             const T& initValue,
             lib::Operator<T> op,
             const std::string& resultMsg) {
    lib::salute(saluteMsg);

    lib::vector<T> arr;

    auto lenPack =
        lib::getValueRetry(getLenMsg, minLenValue, maxLenValue, lib::getInt, maxAttemptsLen);

    if (!lenPack.has_value()) {
        lib::salute(std::format("Error: {}\n", lenPack.error()));
        lib::bye();
        return;
    }
    int len = lenPack.value();

    for (int i = 0; i < len; i++) {
        // fixed format string: include getValueMsg in the output
        auto elementPack = lib::getValueRetry(std::format("Element {}\n{}", i + 1, getValueMsg),
                                              minValue,
                                              maxValue,
                                              getInputValue,
                                              maxAttemptsValue);

        if (!elementPack.has_value()) {
            lib::salute(std::format("Error: {}\n", elementPack.error()));
            lib::bye();
            return;
        }

        arr.push_back(elementPack.value());
    }

    auto resultPack = lib::accumulate(arr, initValue, op);

    if (!resultPack.has_value()) {
        lib::salute(std::format("Error: {}\n", resultPack.error()));
        lib::bye();
        return;
    }

    lib::salute(std::format("{}{}\n", resultMsg, lib::getString(resultPack.value()).value()));

    lib::bye();
}
