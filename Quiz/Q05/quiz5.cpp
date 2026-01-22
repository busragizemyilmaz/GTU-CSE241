#include <iostream>
#include "quiz5.h"

using namespace std;

ostream& operator<<(ostream& os, const Money& other) {
    os << other.dollar << "." << other.cents;

    return os;
}

Money& Money::operator++() {
    this->dollar++;

    return *this;
}

Money Money::operator++(int) {
    Money temp = *this;

    this->dollar++;

    return temp;
}

Money operator+(const int number, const Money& m) {
    return Money(number + m.dollar, m.cents);
}

Money operator+(const Money& m1, const Money& m2) {
    int newDollar = m1.dollar + m2.dollar;
    int newCents = m1.cents + m2.cents;

    if (newCents >= 100)
    {
        newDollar += (newCents / 100);
        newCents %= 100;
    }

    return Money(newDollar, newCents);
}