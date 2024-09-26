#include <iostream>

using namespace std;

int main() {

    typedef int *VEC;
    typedef VEC *MATRIX;

    int a = 5;
    VEC v = &a;
    MATRIX m = &v;

    cout << endl;
    cout << "Display a using v: " << *v << endl;
    cout << "Display a using m: " << **m << endl;

    return 0;

}