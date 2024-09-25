#include <iostream>

using namespace std;

int main() {

    double x, y;
    cout << endl;
    cout << "Enter Double X: ";
    cin >> x;

    cout << "Enter Double Y: ";
    cin >> y;
    cout << endl;

    double *ptr_x = &x, *ptr_y = &y;

    double sum = *ptr_x + *ptr_y;

    cout << "X: " << x << endl;
    cout << "Y: " << y << endl;
    cout << "Sum: " << sum << endl;
 
    return 0;

}