#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<class T>
class ShapeList {
public:
    ShapeList() : name("") { }
    ShapeList(string n) : name(n) { } //copy constructor
    ShapeList(string &&name) noexcept { //move constructor
        this->name = move(name);
    }

    void add(const T& other) {
        data.push_back(other);
    }

    ShapeList& operator=(const ShapeList<T>& other) { //copy assignmnet
        if (this != &other)
            data = other.data;

        return *this;
    }

    ShapeList& operator=(ShapeList<T>&& other) noexcept { //move assignmnet
        if (this != &other)
            data = move(other.data);

        return *this;
    }
private:
    string name;
    vector<T> data;
};

template<class T>
void swaplists(ShapeList<T>& shape1, ShapeList<T>& shape2) 
{
    ShapeList<T> temp;

    temp = move(shape1);
    shape1 = move(shape2);
    shape2 = move(temp);
}