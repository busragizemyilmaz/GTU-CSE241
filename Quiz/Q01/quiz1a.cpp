#include <iostream>
using namespace std;

int main()
{
    double x, y;
    bool flag;

    cout << "Enter x: ";
    cin >> x;
    cout << "Enter y: ";
    cin >> y;

    flag = (x == y);
    if (flag)
        cout << "Comparison: true" << endl;
    else
        cout << "Comparison : false" << endl;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(6);
    cout << "   for " << x << " and " << y << endl;
     
    return 0;
}

