#include "utils.h"

void lib::salute(const std::string& s) { std::cout << s; }

void lib::bye() {
    std::cout << "The program is exiting, press enter to continue..";
    std::cin.get();
}
