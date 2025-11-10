#include "menu.h"
#include <iostream>

int main() {
    try {
        Menu m;
        m.run();
    } catch (const std::exception& e) {
        std::cout << "Fatal: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
