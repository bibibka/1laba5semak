#ifndef DEQUE_ON_QUEUE_H
#define DEQUE_ON_QUEUE_H

#include "base.h"
#include "queue_core.h"

class DequeOnQueue : public INumberContainer {
    QueueCore q_;
public:
    DequeOnQueue(size_t cap = 8) : q_(cap) {
        std::cout << "[DequeOnQueue] ctor\n";
    }
    DequeOnQueue(const DequeOnQueue& other) : q_(other.q_) {
        std::cout << "[DequeOnQueue] copy-ctor\n";
    }
    DequeOnQueue& operator=(const DequeOnQueue& other) {
        std::cout << "[DequeOnQueue] operator=\n";
        if (this != &other) q_ = other.q_;
        return *this;
    }
    ~DequeOnQueue() override {
        std::cout << "[DequeOnQueue] dtor\n";
    }

    // INumberContainer: push = push_back, pop = pop_front
    void push(double value) override { push_back(value); }
    double pop() override { return pop_front(); }
    double front() const override { return q_.peekFront(); }
    double back() const override { return q_.peekBack(); }
    size_t size() const override { return q_.size(); }
    bool empty() const override { return q_.empty(); }
    void clear() override { q_.clear(); }

    void push_back(double v) { q_.enqueue(v); }

    void push_front(double v) {
        QueueCore tmp(q_.size() + 1);
        tmp.enqueue(v);
        size_t n = q_.size();
        for (size_t i = 0; i < n; ++i) tmp.enqueue(q_.dequeue());
        q_ = tmp;
    }

    double pop_front() { return q_.dequeue(); }

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

    void print(std::ostream& os) const override {
        os << "Deque ";
        q_.print(os);
    }

    void serialize(std::ostream& os) const override {
        os << "DEQUE " << q_.size() << "\n";
        QueueCore copy = q_;
        size_t n = copy.size();
        for (size_t i = 0; i < n; ++i) os << copy.dequeue() << "\n";
    }

    void deserialize(std::istream& is) override {
        std::string tag; size_t n;
        if (!(is >> tag >> n)) throw FileError("bad deque header");
        if (tag != "DEQUE") throw FileError("expected DEQUE");
        q_.clear();
        for (size_t i = 0; i < n; ++i) {
            double v; if (!(is >> v)) throw FileError("bad deque data");
            q_.enqueue(v);
        }
    }
};

#endif // DEQUE_ON_QUEUE_H
