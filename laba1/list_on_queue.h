#ifndef LIST_ON_QUEUE_H
#define LIST_ON_QUEUE_H

#include "base.h"
#include "queue_core.h"

class ListOnQueue : public INumberContainer {
    QueueCore q_;
public:
    ListOnQueue(size_t cap = 8) : q_(cap) {
        std::cout << "[ListOnQueue] ctor\n";
    }
    ListOnQueue(const ListOnQueue& other) : q_(other.q_) {
        std::cout << "[ListOnQueue] copy-ctor\n";
    }
    ListOnQueue& operator=(const ListOnQueue& other) {
        std::cout << "[ListOnQueue] operator=\n";
        if (this != &other) q_ = other.q_;
        return *this;
    }
    ~ListOnQueue() override {
        std::cout << "[ListOnQueue] dtor\n";
    }

    // Базовые: трактуем push как push_back
    void push(double value) override { q_.enqueue(value); }
    double pop() override { return pop_front(); }
    double front() const override { return q_.peekFront(); }
    double back() const override { return q_.peekBack(); }
    size_t size() const override { return q_.size(); }
    bool empty() const override { return q_.empty(); }
    void clear() override { q_.clear(); }

    // Специфичные операции списка
    void push_front(double v) {
        QueueCore tmp(q_.size() + 1);
        tmp.enqueue(v);
        size_t n = q_.size();
        for (size_t i = 0; i < n; ++i) tmp.enqueue(const_cast<ListOnQueue*>(this)->q_.dequeue());
        q_ = tmp;
    }

    void push_back(double v) { q_.enqueue(v); }

    double pop_front() {
        return q_.dequeue();
    }

    double pop_back() {
        if (q_.empty()) throw QueueError("pop_back from empty");
        QueueCore tmp(q_.size());
        double last = 0.0;
        size_t n = q_.size();
        for (size_t i = 0; i < n; ++i) {
            double cur = q_.dequeue();
            if (i + 1 == n) last = cur;
            else tmp.enqueue(cur);
        }
        q_ = tmp;
        return last;
    }

    // Вставка по индексу [0..size]
    void insert(size_t index, double v) {
        if (index > q_.size()) throw IndexError("insert index out of range");
        QueueCore tmp(q_.size() + 1);
        size_t n = q_.size();
        for (size_t i = 0; i < n; ++i) {
            if (i == index) tmp.enqueue(v);
            tmp.enqueue(q_.dequeue());
        }
        if (index == n) tmp.enqueue(v);
        q_ = tmp;
    }

    // Удаление по индексу [0..size-1]
    double erase(size_t index) {
        if (index >= q_.size()) throw IndexError("erase index out of range");
        QueueCore tmp(q_.size());
        double removed = 0.0;
        size_t n = q_.size();
        for (size_t i = 0; i < n; ++i) {
            double cur = q_.dequeue();
            if (i == index) removed = cur;
            else tmp.enqueue(cur);
        }
        q_ = tmp;
        return removed;
    }

    // Доступ по индексу (медленный, но через очередь)
    double at(size_t index) const {
        if (index >= q_.size()) throw IndexError("at index out of range");
        QueueCore copy = q_;
        for (size_t i = 0; i < index; ++i) copy.dequeue();
        return copy.dequeue();
    }

    void set(size_t index, double value) {
        if (index >= q_.size()) throw IndexError("set index out of range");
        QueueCore tmp(q_.size());
        size_t n = q_.size();
        for (size_t i = 0; i < n; ++i) {
            double cur = q_.dequeue();
            if (i == index) tmp.enqueue(value);
            else tmp.enqueue(cur);
        }
        q_ = tmp;
    }

    void print(std::ostream& os) const override {
        os << "List ";
        q_.print(os);
    }

    // Сериализация: тип, размер, элементы
    void serialize(std::ostream& os) const override {
        os << "LIST " << q_.size() << "\n";
        QueueCore copy = q_;
        size_t n = copy.size();
        for (size_t i = 0; i < n; ++i) {
            os << copy.dequeue() << "\n";
        }
    }

    void deserialize(std::istream& is) override {
        std::string tag;
        size_t n;
        if (!(is >> tag >> n)) throw FileError("bad list header");
        if (tag != "LIST") throw FileError("expected LIST");
        q_.clear();
        for (size_t i = 0; i < n; ++i) {
            double v;
            if (!(is >> v)) throw FileError("bad list data");
            q_.enqueue(v);
        }
    }
};

#endif // LIST_ON_QUEUE_H
