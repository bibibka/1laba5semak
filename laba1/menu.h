#ifndef MENU_H
#define MENU_H

#include "io.h"
#include <iostream>
#include <limits>

class Menu {
    Bundle bundle_;

    static void pause() {
        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    static double readDouble() {
        double v;
        if (!(std::cin >> v)) throw std::runtime_error("input error");
        return v;
    }

    static size_t readIndex() {
        long long x;
        if (!(std::cin >> x) || x < 0) throw std::runtime_error("index must be >= 0");
        return static_cast<size_t>(x);
    }

    void listMenu() {
        for (;;) {
            std::cout << "\n== List Menu ==\n"
                         "1) push_back\n"
                         "2) push_front\n"
                         "3) pop_back\n"
                         "4) pop_front\n"
                         "5) insert(index, value)\n"
                         "6) erase(index)\n"
                         "7) set(index, value)\n"
                         "8) at(index)\n"
                         "9) print\n"
                         "10) clear\n"
                         "0) back\n> ";
            int c; if (!(std::cin >> c)) return;
            try {
                if (c == 0) return;
                if (c == 1) { std::cout << "value: "; double v = readDouble(); bundle_.list.push_back(v); }
                else if (c == 2) { std::cout << "value: "; double v = readDouble(); bundle_.list.push_front(v); }
                else if (c == 3) { std::cout << "popped: " << bundle_.list.pop_back() << "\n"; }
                else if (c == 4) { std::cout << "popped: " << bundle_.list.pop_front() << "\n"; }
                else if (c == 5) { std::cout << "index value: "; size_t i = readIndex(); double v = readDouble(); bundle_.list.insert(i, v); }
                else if (c == 6) { std::cout << "index: "; size_t i = readIndex(); std::cout << "erased: " << bundle_.list.erase(i) << "\n"; }
                else if (c == 7) { std::cout << "index value: "; size_t i = readIndex(); double v = readDouble(); bundle_.list.set(i, v); }
                else if (c == 8) { std::cout << "index: "; size_t i = readIndex(); std::cout << "at: " << bundle_.list.at(i) << "\n"; }
                else if (c == 9) { bundle_.list.print(std::cout); std::cout << "\n"; }
                else if (c == 10){ bundle_.list.clear(); std::cout << "cleared\n"; }
                else std::cout << "unknown\n";
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
    }

    void dequeMenu() {
        for (;;) {
            std::cout << "\n== Deque Menu ==\n"
                         "1) push_back\n"
                         "2) push_front\n"
                         "3) pop_back\n"
                         "4) pop_front\n"
                         "5) front/back\n"
                         "6) print\n"
                         "7) clear\n"
                         "0) back\n> ";
            int c; if (!(std::cin >> c)) return;
            try {
                if (c == 0) return;
                if (c == 1) { std::cout << "value: "; double v = readDouble(); bundle_.deq.push_back(v); }
                else if (c == 2) { std::cout << "value: "; double v = readDouble(); bundle_.deq.push_front(v); }
                else if (c == 3) { std::cout << "popped: " << bundle_.deq.pop_back() << "\n"; }
                else if (c == 4) { std::cout << "popped: " << bundle_.deq.pop_front() << "\n"; }
                else if (c == 5) { std::cout << "front: " << bundle_.deq.front() << " back: " << bundle_.deq.back() << "\n"; }
                else if (c == 6) { bundle_.deq.print(std::cout); std::cout << "\n"; }
                else if (c == 7) { bundle_.deq.clear(); std::cout << "cleared\n"; }
                else std::cout << "unknown\n";
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
    }

    void stackMenu() {
        for (;;) {
            std::cout << "\n== Stack Menu ==\n"
                         "1) push\n"
                         "2) pop\n"
                         "3) top/front\n"
                         "4) print\n"
                         "5) clear\n"
                         "0) back\n> ";
            int c; if (!(std::cin >> c)) return;
            try {
                if (c == 0) return;
                if (c == 1) { std::cout << "value: "; double v = readDouble(); bundle_.st.push(v); }
                else if (c == 2) { std::cout << "popped: " << bundle_.st.pop() << "\n"; }
                else if (c == 3) { std::cout << "top: " << bundle_.st.front() << "\n"; }
                else if (c == 4) { bundle_.st.print(std::cout); std::cout << "\n"; }
                else if (c == 5) { bundle_.st.clear(); std::cout << "cleared\n"; }
                else std::cout << "unknown\n";
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
    }

public:
    Menu() { std::cout << "[Menu] ctor\n"; }
    ~Menu() { std::cout << "[Menu] dtor\n"; }

    void run() {
        for (;;) {
            std::cout << "\n== Main Menu ==\n"
                         "1) List\n"
                         "2) Deque\n"
                         "3) Stack\n"
                         "4) Save to file\n"
                         "5) Load from file\n"
                         "0) Exit\n> ";
            int c; if (!(std::cin >> c)) return;
            try {
                if (c == 0) return;
                if (c == 1) listMenu();
                else if (c == 2) dequeMenu();
                else if (c == 3) stackMenu();
                else if (c == 4) {
                    std::cout << "filename: ";
                    std::string fn; std::cin >> fn;
                    saveToFile(fn.c_str(), bundle_);
                    std::cout << "saved\n";
                } else if (c == 5) {
                    std::cout << "filename: ";
                    std::string fn; std::cin >> fn;
                    loadFromFile(fn.c_str(), bundle_);
                    std::cout << "loaded\n";
                } else {
                    std::cout << "unknown\n";
                }
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
    }
};

#endif // MENU_H
