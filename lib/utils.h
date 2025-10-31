#ifndef _LIB_UTILS_H_
#define _LIB_UTILS_H_

#include <expected>
#include <format>
#include <iostream>
#include <regex>
#include <string>

#include "../vector/vector.h"

using std::cin, std::cout;
using std::expected;
using std::format;
using std::smatch, std::regex_match;
using std::string;
using std::unexpected;

namespace lib {
template <class T>
using Operator = expected<T, string> (*)(const T&, const T&);

template <class T>
using Condition = bool (*)(const T&);

template <class T>
using extractBuffer = expected<T, string> (*)(const string&, const T&, const T&);

template <class T>
expected<T, string> getValue(const string& message,
                             const T& minValue,
                             const T& maxValue,
                             extractBuffer<T> extract);

template <class T>
expected<T, string> getValueRetry(const string& message,
                                  const T& minValue,
                                  const T& maxValue,
                                  extractBuffer<T> extract,
                                  int maxAttempts = 5);

template <class T>
expected<T, string> accumulate(const lib::vector<T>& v, const T& init, Operator<T> op);

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

template <class T>
expected<T, string> lib::getValue(const string& message,
                                  const T& minValue,
                                  const T& maxValue,
                                  extractBuffer<T> extract) {
    cout << message;

    string buffer;
    getline(cin, buffer);

    auto result = extract(buffer, minValue, maxValue);

    if (!result.has_value()) {
        return unexpected(result.error());
    }

    return result.value();
}

template <class T>
expected<T, string> lib::getValueRetry(const string& message,
                                       const T& minValue,
                                       const T& maxValue,
                                       extractBuffer<T> extract,
                                       int maxAttempts) {
    int failedCounts = 0;

    while (failedCounts < maxAttempts) {
        auto result = getValue(message, minValue, maxValue, extract);
        if (!result.has_value()) {
            failedCounts++;
            cout << "Error: " << result.error() << "\nYou have " << maxAttempts - failedCounts
                 << " times left\n";
            if (failedCounts < maxAttempts) {
                cout << "Please try again\n";
            }
        } else {
            return result.value();
        }
    }

    return unexpected(format("Exceeded the max attempts: {}", maxAttempts));
}

#endif  // !_LIB_UTILS_H_
