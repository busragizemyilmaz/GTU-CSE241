#include <iostream>
#include <memory>
#include <cstdlib> // for rand()
#include <vector>
#include <stdexcept>
#include <typeinfo>
#include <string>

using namespace std;

class OutOfBound : public exception {
public:
    OutOfBound(const string& msg) : message(msg) { }
    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    string message;
};

template<class T>
class Matrix {
public:
    Matrix() : matrix(nullptr) { }
    Matrix(int n, int m) : row(n), col(m) {
        matrix = make_unique<T[]>(row * col);
    }

    ~Matrix() {
        
    }

    void random() {
        for (int i = 0; i < row * col; i++)
        {
            if (typeid(T) == typeid(int))
                matrix[i] = rand() % 101;
            else
                matrix[i] = (((double)rand() / RAND_MAX) * 2) - 1.0;
        }
    }

    vector<T> operator[](int index) throw(OutOfBound) {
        vector<T> data;

        if (index >= 1 && index <= row)
        {
            for (int i = 0; i < col; i++)
            {
                data.push_back(matrix[(index - 1) * col + i]);
            }
        }

        else
        {
            throw OutOfBound("Row index out of bond.");
        }

        return data;
    }

    void set(int r, int c, T v) throw(OutOfBound) {
        if (r >= 1 && r <= row && c >= 1 && c <= col)
        {
            matrix[(r - 1) * col + (c - 1)] = v;
        }

        else 
            throw OutOfBound("Index out of bound in set()");
    }

    class Iterator {
    public:
        Iterator(T *p) : ptr(p) { }

        T& operator*() {
            return *ptr;
        }

        Iterator& operator++() {
            ptr++;

            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;

            ptr++;

            return temp;
        }

        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        }
    private:
        T *ptr;
    };

    Iterator begin() {
        return Iterator(matrix.get()); //matrix.get() başlangıç adresi verir.
    }

    Iterator end() {
        return Iterator(matrix.get() + (row * col));
    }
private:
    int row;
    int col;
    unique_ptr<T[]> matrix;
};