#ifndef _LIB_INTEGER_H_
#define _LIB_INTEGER_H_

#include <climits>
#include <expected>
#include <format>
#include <iostream>
#include <regex>
#include <string>

using std::cout, std::cin, std::ostream, std::istream;
using std::expected;
using std::format;
using std::regex;
using std::regex_match;
using std::smatch;
using std::string;
using std::unexpected;

namespace lib {
expected<int, string> extractInt(const string& buffer, const int& minValue = INT_MIN,
                                 const int& maxValue = INT_MAX);
}

#endif  // !_LIB_INTEGER_H_
