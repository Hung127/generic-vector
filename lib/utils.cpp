#include "utils.h"

void lib::salute(const std::string& s) { cout << s; }

void lib::bye() {
    cout << "The program is exiting, press enter to continue..";
    cin.get();
}
