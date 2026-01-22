#ifndef MONEY_H
#define MONEY_H

#include <iostream>

class Money {
public:
    Money() : dollar(0), cents(0) { }
    Money(int d, int c) : dollar(d), cents(c) { }
    friend std::ostream& operator<<(std::ostream& os, const Money& other);
    Money& operator++();
    Money operator++(int);
    friend Money operator+(const int number, const Money& m);
    friend Money operator+(const Money& m1, const Money& m2);
private:
    int dollar;
    int cents;
};

#endif