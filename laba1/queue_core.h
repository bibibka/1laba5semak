#ifndef QUEUE_CORE_H
#define QUEUE_CORE_H

#include <iostream>
#include "exceptions.h"

class QueueCore {
    double* data_;
    size_t cap_;
    size_t head_;
    size_t tail_;
    size_t count_;

    void grow() {
        size_t newCap = cap_ ? cap_ * 2 : 4;
        double* nd = new double[newCap];
        for (size_t i = 0; i < count_; ++i) {
            nd[i] = data_[(head_ + i) % cap_];
        }
        delete[] data_;
        data_ = nd;
        cap_ = newCap;
        head_ = 0;
        tail_ = count_;
    }

public:
    QueueCore(size_t cap = 8)
        : data_(nullptr), cap_(0), head_(0), tail_(0), count_(0) {
        std::cout << "[QueueCore] ctor(cap=" << cap << ")\n";
        if (cap < 1) cap = 1;
        data_ = new double[cap];
        cap_ = cap;
    }

    QueueCore(const QueueCore& other)
        : data_(nullptr), cap_(other.cap_), head_(other.head_), tail_(other.tail_), count_(other.count_) {
        std::cout << "[QueueCore] copy-ctor\n";
        data_ = new double[cap_];
        for (size_t i = 0; i < count_; ++i) {
            data_[i] = other.data_[(other.head_ + i) % other.cap_];
        }
        head_ = 0;
        tail_ = count_;
    }

    QueueCore& operator=(const QueueCore& other) {
        std::cout << "[QueueCore] operator=\n";
        if (this == &other) return *this;
        delete[] data_;
        cap_ = other.cap_;
        data_ = new double[cap_];
        count_ = other.count_;
        for (size_t i = 0; i < count_; ++i) {
            data_[i] = other.data_[(other.head_ + i) % other.cap_];
        }
        head_ = 0;
        tail_ = count_;
        return *this;
    }

    ~QueueCore() {
        std::cout << "[QueueCore] dtor\n";
        delete[] data_;
    }

    void setCapacity(size_t newCap) {
        if (newCap < count_) throw QueueError("new capacity < size");
        double* nd = new double[newCap];
        for (size_t i = 0; i < count_; ++i)
            nd[i] = data_[(head_ + i) % cap_];
        delete[] data_;
        data_ = nd;
        cap_ = newCap;
        head_ = 0;
        tail_ = count_;
    }

    size_t capacity() const { return cap_; }

    void enqueue(double v) {
        if (count_ == cap_) grow();
        data_[tail_] = v;
        tail_ = (tail_ + 1) % cap_;
        ++count_;
    }

    double dequeue() {
        if (count_ == 0) throw QueueError("dequeue from empty");
        double v = data_[head_];
        head_ = (head_ + 1) % cap_;
        --count_;
        return v;
    }

    double peekFront() const {
        if (count_ == 0) throw QueueError("peek front empty");
        return data_[head_];
    }

    double peekBack() const {
        if (count_ == 0) throw QueueError("peek back empty");
        size_t idx = (tail_ + cap_ - 1) % cap_;
        return data_[idx];
    }

    size_t size() const { return count_; }
    bool empty() const { return count_ == 0; }

    void clear() {
        head_ = tail_ = count_ = 0;
    }

    void print(std::ostream& os) const {
        os << "[";
        for (size_t i = 0; i < count_; ++i) {
            if (i) os << ", ";
            os << data_[(head_ + i) % cap_];
        }
        os << "]";
    }
};

#endif // QUEUE_CORE_H
