#ifndef _LIB_UTILS_H_
#define _LIB_UTILS_H_

#include <expected>
#include <format>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

#include "../vector/vector.h"

using std::cin, std::cout;
using std::expected;
using std::format;
using std::ostringstream;
using std::smatch, std::regex_match;
using std::string;
using std::unexpected;

namespace lib {
template <class T>
using Operator = expected<T, string> (*)(const T&, const T&);

template <class T, class MaxMinT>
using BoundedInputReaderFn = expected<T, string> (*)(const string&, const MaxMinT&, const MaxMinT&);

template <class T>
using Condition = bool (*)(const T&);

// template <class T>
// using extractBuffer = expected<T, string> (*)(const string&, const T&, const T&);

template <class T, class MaxMinT>
expected<T, string> getValueRetry(const string& message,
                                  const MaxMinT& minValue,
                                  const MaxMinT& maxValue,
                                  BoundedInputReaderFn<T, MaxMinT> getInput,
                                  int maxAttempts = 5);

template <class T>
expected<T, string> accumulate(const lib::vector<T>& v, const T& init, Operator<T> op);

template <class T>
expected<string, string> getString(const T& value);

void salute(const std::string& s);
void bye();

}  // namespace lib

template <class T>
expected<T, string> lib::accumulate(const lib::vector<T>& v, const T& init, lib::Operator<T> op) {
    int len = v.size();
    T result = init;
    for (int i = 0; i < len; i++) {
        if (v[i].has_value()) {
            auto resultPack = op(result, v[i].value());
            result = resultPack.has_value() ? resultPack.value() : result;
        }
    }
    return result;
}

template <class T, class MaxMinT>
expected<T, string> lib::getValueRetry(const string& message,
                                       const MaxMinT& minValue,
                                       const MaxMinT& maxValue,
                                       lib::BoundedInputReaderFn<T, MaxMinT> getInput,
                                       int maxAttempts) {
    int failedCounts = 0;

    while (failedCounts < maxAttempts) {
        auto result = getInput(message, minValue, maxValue);

        if (!result.has_value()) {
            failedCounts++;
            lib::salute(format("Error: {}\n", result.error()));
            if (failedCounts < maxAttempts) {
                cout << "\nYou have " << maxAttempts - failedCounts
                     << " times left\n Please try again\n";
            }
        } else {
            return result.value();
        }
    }

    if (maxAttempts == 1) {
        return unexpected("Failed in getting input");
    }

    return unexpected(format("Exceeded the max attempts: {}", maxAttempts));
}

template <class T>
expected<string, string> lib::getString(const T& value) {
    ostringstream os;
    os << value;
    return os.str();
}

#endif  // !_LIB_UTILS_H_
