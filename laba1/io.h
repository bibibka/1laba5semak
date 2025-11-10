#ifndef IO_H
#define IO_H

#include <iostream>
#include <fstream>
#include "base.h"
#include "list_on_queue.h"
#include "deque_on_queue.h"
#include "stack_on_queue.h"
#include "exceptions.h"

enum class ContainerKind { LIST = 1, DEQUE = 2, STACK = 3 };

struct Bundle : public ISerializable {
    ListOnQueue list;
    DequeOnQueue deq;
    StackOnQueue st;

    Bundle() : list(8), deq(8), st(8) {
        std::cout << "[Bundle] ctor\n";
    }
    Bundle(const Bundle& b) : list(b.list), deq(b.deq), st(b.st) {
        std::cout << "[Bundle] copy-ctor\n";
    }
    Bundle& operator=(const Bundle& b) {
        std::cout << "[Bundle] operator=\n";
        if (this != &b) {
            list = b.list; deq = b.deq; st = b.st;
        }
        return *this;
    }
    ~Bundle() override { std::cout << "[Bundle] dtor\n"; }

    void serialize(std::ostream& os) const override {
        os << "BUNDLE 3\n";
        list.serialize(os);
        deq.serialize(os);
        st.serialize(os);
    }

    void deserialize(std::istream& is) override {
        std::string tag; size_t cnt;
        if (!(is >> tag >> cnt)) throw FileError("bad bundle header");
        if (tag != "BUNDLE" || cnt != 3) throw FileError("expected BUNDLE 3");
        list.deserialize(is);
        deq.deserialize(is);
        st.deserialize(is);
    }
};

inline void saveToFile(const char* filename, const Bundle& b) {
    std::ofstream ofs(filename);
    if (!ofs) throw FileError("cannot open file to write");
    b.serialize(ofs);
}

inline void loadFromFile(const char* filename, Bundle& b) {
    std::ifstream ifs(filename);
    if (!ifs) throw FileError("cannot open file to read");
    b.deserialize(ifs);
}

#endif // IO_H
