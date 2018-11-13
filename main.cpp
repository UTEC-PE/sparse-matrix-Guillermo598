#include <iostream>

#include "matrix.h"

using namespace std;

int main(int argc, char *argv[]) {
    Matrix<int> a(5, 5);
    Matrix<int> b(5, 5);
    a.set(4,1,4);
    a.set(3,3,7);
    b.set(0,0,3);
    b.set(2,2,8);

    Matrix<int> c(2, 2);
    Matrix<int> d(2, 2);
    c.set(0,0,1);
    c.set(1,0,1);
    c.set(1,1,1);

    d.set(0,0,1);
    d.set(0,1,1);
    d.set(1,1,1);

    Matrix<int> e = c * d;
    Matrix<int> t = e.transposed();
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++)
            cout << t(j, i) << " ";
        cout << endl;
    }
    return EXIT_SUCCESS;
}