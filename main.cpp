#include "main.h"

#include "./Student/Student.h"
#include "./lib/integer.h"
#include "./lib/utils.h"
#include "./vector/vector.h"

using std::cin, std::cout;

int main() {
    main01();
    return 0;
}

void salute(const std::string& s) { cout << s; }
void bye() {
    cout << "The program is exiting, press enter to continue..";
    cin.get();
}

template <class T>
void process(const string& saluteMsg,
             const string& getLenMsg,
             int minLenValue,
             int maxLenValue,
             const T& minValue,
             const T& maxValue,
             const string& getValueMsg,
             lib::extractBuffer<T> extract,
             int maxAttempts,
             const T& initValue,
             lib::Operator<T> op,
             const string& resultMsg);
// 1. Nhập vào số nguyên n [2-10], không nhập sai quá 5 lần.

//       Nếu nhập sai lần thứ 5: thoát chương trình

// 2. Nhập n số nguyên, mỗi số thuộc [10, 100] vào mảng một chiều,

//       Không nhập sai quá 3 lần mỗi số,

//       Reset lại số lần thử về tối đa 3 cho số kế tiếp nếu nhập đúng trước đó

// 3. Tính tổng các số chẵn

// 4. In kết quả tổng dãy số ra màn hình
//

// void main01() {
//     salute("This is a program that calculate the sum of all the even number in an array\n");
//
//     auto lenPack = lib::getValueRetry("Enter array length: ", 2, 10, lib::extractInt);
//     if (!lenPack.has_value()) {
//         bye();
//         return;
//     }
//
//     int len = lenPack.value();
//     lib::vector<int> arr(len);
//     for (int i = 0; i < len; i++) {
//         auto num =
//             lib::getValueRetry(std::format("Enter arr[{}]: ", i + 1), 10, 100,
//             lib::extractInt, 3);
//         if (!num.has_value()) {
//             bye();
//             return;
//         }
//         arr.push_back(num.value());
//     }
//
//     int init = 0;
//     int res = lib::accumulate(
//         arr,
//         init,
//         // use +[]() -> int to make lambda function a function pointer
//         +[](const int& a, const int& b) -> int { return (b % 2 == 0 ? (a + b) : a); });
//
//     cout << format("Sum of all even elements in array is {}\n", res);
//
//     bye();
// }
//
void main01() {
    process(
        "This is a program that ask you to enter a vector, it will calculate the sum of all "
        "elements that are even in that vector\n",
        "Enter len: ",
        2,
        10,
        2,
        100,
        "Enter integer: ",
        lib::extractInt,
        5,
        0,
        +[](const int& a, const int& b) -> expected<int, string> {
            return b % 2 == 0 ? (a + b) : a;
        },
        "The sum of all even elements is: ");
}

// - GPA là điểm trung bình (float)

// 1. Nhập vào số nguyên n [2-10], không nhập sai quá 5 lần.

//       Nếu nhập sai lần thứ 5: thoát chương trình

// 2. Nhập vào n sinh viên vào mảng một chiều

// 3. Tìm sinh viên có điểm trung bình lớn nhất

// 4. In toàn bộ thông tin sinh viên này ra màn hình. Nếu có nhiều sinh viên

//    cùng điểm trung bình, chỉ cần in ra 1 sinh viên đầu tiên.
void main02() {}

template <class T>
void process(const string& saluteMsg,
             const string& getLenMsg,
             int minLenValue,
             int maxLenValue,
             const T& minValue,
             const T& maxValue,
             const string& getValueMsg,
             lib::extractBuffer<T> extract,
             int maxAttempts,
             const T& initValue,
             lib::Operator<T> op,
             const string& resultMsg) {
    salute(saluteMsg);

    lib::vector<T> arr;

    auto lenPack =
        lib::getValueRetry(getLenMsg, minLenValue, maxLenValue, lib::extractInt, maxAttempts);
    if (!lenPack.has_value()) {
        salute(format("Error: {}\n", lenPack.error()));
        bye();
        return;
    }
    int len = lenPack.value();

    for (int i = 0; i < len; i++) {
        auto elementPack = lib::getValueRetry(format("Element {}\n\t{}", i + 1, getValueMsg),
                                              minValue,
                                              maxValue,
                                              extract,
                                              maxAttempts);

        if (!elementPack.has_value()) {
            cout << "Error: " << elementPack.error() << "\n";
            bye();
            return;
        }

        arr.push_back(elementPack.value());
    }

    auto resultPack = lib::accumulate(arr, initValue, op);

    if (!resultPack.has_value()) {
        salute(format("Error: {}\n", resultPack.error()));
        bye();
        return;
    }

    salute(format("{}{}\n", resultMsg, resultPack.value()));

    bye();
}
