#ifndef STACK_ON_QUEUE_H
#define STACK_ON_QUEUE_H

#include "base.h"
#include "queue_core.h"

class StackOnQueue : public INumberContainer {
    QueueCore q_;
public:
    StackOnQueue(size_t cap = 8) : q_(cap) {
        std::cout << "[StackOnQueue] ctor\n";
    }
    StackOnQueue(const StackOnQueue& other) : q_(other.q_) {
        std::cout << "[StackOnQueue] copy-ctor\n";
    }
    StackOnQueue& operator=(const StackOnQueue& other) {
        std::cout << "[StackOnQueue] operator=\n";
        if (this != &other) q_ = other.q_;
        return *this;
    }
    ~StackOnQueue() override {
        std::cout << "[StackOnQueue] dtor\n";
    }

    // Реализация стека на одной очереди:
    // push: enqueue, затем вращение предыдущих элементов
    void push(double value) override {
        size_t n = q_.size();
        q_.enqueue(value);
        // вращаем n элементов назад, чтобы новый стал "сверху"
        for (size_t i = 0; i < n; ++i) {
            double x = q_.dequeue();
            q_.enqueue(x);
        }
    }

    double pop() override {
        // верхний элемент сейчас во фронте
        return q_.dequeue();
    }

    double front() const override { // top
        return q_.peekFront();
    }

    double back() const override { // низ стека
        return q_.peekBack();
    }

    size_t size() const override { return q_.size(); }
    bool empty() const override { return q_.empty(); }
    void clear() override { q_.clear(); }

    void print(std::ostream& os) const override {
        os << "Stack ";
        q_.print(os);
    }

    void serialize(std::ostream& os) const override {
        os << "STACK " << q_.size() << "\n";
        QueueCore copy = q_;
        size_t n = copy.size();
        for (size_t i = 0; i < n; ++i) os << copy.dequeue() << "\n";
    }

    void deserialize(std::istream& is) override {
        std::string tag; size_t n;
        if (!(is >> tag >> n)) throw FileError("bad stack header");
        if (tag != "STACK") throw FileError("expected STACK");
        q_.clear();
        // Восстанавливаем очередь так, чтобы top оказался во фронте.
        // Запишем элементы как есть — порядок печати/сохранения неизменен.
        for (size_t i = 0; i < n; ++i) {
            double v; if (!(is >> v)) throw FileError("bad stack data");
            q_.enqueue(v);
        }
    }
};

#endif // STACK_ON_QUEUE_H
