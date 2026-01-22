#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template<class T>
class NotFoundException : public exception {
public:
    NotFoundException(T v) : value(v) { }
    const char* what() const noexcept override {
        return "Error: Element not found in the set.";
    }
        
    T getValue() const { return value; }
private:
    T value;
};

template<class T>
class Set {
public:
    Set() { }
    Set(const Set<T>& other) {
        data = other.data;
    }

    Set& operator=(const Set<T>& other) {
        if (this != &other)
        {
            data.clear();
            data = other.data;
        }

        return *this;
    }

    ~Set() {
        data.clear();
    }

    void add(T e) {
        if (!ismember(e))
            data.push_back(e);
    }

    void remove(T e) throw(NotFoundException<T>) {
        int index;

        if (ismember(e))
        {
            for (int i = 0; i < data.size(); i++)
            {
                if (data[i] == e)
                    index = i;
            }

            for (int i = index; i < data.size() - 1; i++)
                data[i] = data[i + 1];
            data.pop_back();
        }

        else 
        {
            throw NotFoundException<T>(e);
        }
    }

    bool ismember(T e) {
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i] == e)
                return true;
        }

        return false;
    }


private:
    vector<T> data;
};