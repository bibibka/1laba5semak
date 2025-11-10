#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <cstring>

class ISerializable {
public:
    virtual void serialize(std::ostream& os) const = 0;
    virtual void deserialize(std::istream& is) = 0;
    virtual ~ISerializable() {}
};

class INumberContainer : public ISerializable {
public:
    virtual void push(double value) = 0;
    virtual double pop() = 0;
    virtual double front() const = 0;
    virtual double back() const = 0;
    virtual size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual void clear() = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual ~INumberContainer() {}
};

#endif // BASE_H
