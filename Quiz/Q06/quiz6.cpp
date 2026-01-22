#include <iostream>
#include "quiz6.h"

using namespace std;

void Money::print() {
    cout << type << wholeNumber << ".";
     
    if (fraction < 10)
        cout << "0";
    
    cout << fraction << endl;
}

int Money::getWholeNumber() {
    return wholeNumber;
}

int Money::getFraction() {
    return fraction;
}

YTL YTL::add(USD& other, double rate) {
    double usdAmount = other.getWholeNumber() + (other.getFraction() / 100.0);
    double convertTL = usdAmount * rate;
    double currentTL = wholeNumber + (fraction / 100.0);
    double sumTL = convertTL + currentTL;

    int newLira = (int)sumTL;
    int newKurus = (int)((sumTL- newLira) * 100.0 + 0.5);

    if (newKurus >= 100)
    {
        newLira += (newKurus / 100);
        newKurus %= 100;
    }

    return YTL(newLira, newKurus);
}