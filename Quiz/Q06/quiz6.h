#ifndef MONEY_H
#define MONEY_H

#include <iostream>
#include <string>

class Money {
public:
    Money() : wholeNumber(0), fraction(0), type("") { }
    Money(int n1, int n2) : wholeNumber(n1), fraction(n2) { }
    void print();
    int getWholeNumber();
    int getFraction();
protected:
    int wholeNumber;
    int fraction;
    std::string type;
};

class USD : public Money {
public:
    USD(int dollar, int cents) : Money(dollar, cents) { 
        type = "USD";
    }
};

class YTL : public Money {
public:
    YTL(int lira, int kurus) : Money(lira, kurus) {
        type = "TL";
    }
    YTL add(USD& other, double rate);
};

#endif