#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>

struct QueueError : public std::runtime_error {
    explicit QueueError(const char* msg) : std::runtime_error(msg) {}
};

struct IndexError : public std::runtime_error {
    explicit IndexError(const char* msg) : std::runtime_error(msg) {}
};

struct FileError : public std::runtime_error {
    explicit FileError(const char* msg) : std::runtime_error(msg) {}
};

#endif // EXCEPTIONS_H
