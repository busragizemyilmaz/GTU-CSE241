#include <iostream>
#include <vector>

using namespace std;

// Quizde "Assume implemented" denilen sınıflar (Test için gerekli)
class Shape {
public:
    virtual double area() const = 0;      // Pure virtual
    virtual void printInfo() const { }    // Virtual
    virtual ~Shape() {}                   // Destructor (Dynamic cast için önemli)
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override { return 3.14 * radius * radius; }
};

class Rectangle : public Shape {
    double w, h;
public:
    Rectangle(double width, double height) : w(width), h(height) {}
    double area() const override { return w * h; }
};
// -----------------------------------------------------------------------

template<class T>
class ShapeContainer {
public:
    void add(T* s) {
        shapes.push_back(s);
    }

    double totalArea() {
        double sum = 0;

        for (int i = 0; i < shapes.size(); i++)
            sum += shapes[i]->area();

        return sum;
    }

    int numberOfCircle()
    {
        int count = 0;

        for (int i = 0; i < shapes.size(); i++)
        {
            Circle *cs = dynamic_cast<Circle*>(shapes[i]);

            if (cs != nullptr)
                count++;
        }

        return count;
    }

private:
    vector<T*> shapes;
};

int main()
{
    ShapeContainer<Shape> objects;

    objects.add(new Circle(2.5));
    objects.add(new Rectangle(2,3));
    
    cout << "Total Area: " << objects.totalArea() << endl;

    cout << "Number of Circles: " << objects.numberOfCircle() << endl;

    return 0;
}