#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define DEBUG


template <class T>
using ELEM = vector<T>;

template <class T>
using VEC = vector<ELEM<T>>;

template <class T>
using action_t = T (*)(int);

template <class T>
using pred_t = bool (*)(T);

template <class T>
using map_t = T (*)(T,T);

// *********************************************************
// FUNCTIONS

template <class T>
T add (T a, T b) {
    return a + b;
}

template <class T>
T positive(int a) {
    T b;
    if (a > 0)
        b = 1;
    else
        b = 0;
    return b;
}

int max(int a, int b) {
    return ((a > b) ? a : b);
}

template <class T>
bool compare (T a) {
    return a > 0;
}

template <class T>
int lenVEC(VEC<T> const &v) {
    int len = 0;
    for (auto a : v)
        len++;
    return len;
}

template <class T>
void printElem(ELEM<T> &v) {
    for (int i = 0; i < v.size(); i++) {
        if (i != v.size()-1)
            cout << v[i] << ", ";
        else 
            cout << v[i];
    }
}

template <class T>
void printVec(VEC<T> &v) {
    cout << "[";
    for (int i = 0; i < v.size(); i++) {
        cout << "[";
        printElem(v[i]);
        if (i == v.size()-1)
            cout << "]";
        else
            cout << "], ";
    }
    cout << "]" << endl;
}

template <class T>
void initVEC(VEC<T> &v, ELEM<T> &&elem) {
    v.push_back(elem);
}

template <typename T>
VEC<T> zip(VEC<T> &v, VEC<T> &w) {

    int colSize, rowSize;
    if (v.size() == 1) {
        colSize = v.size() * 2;
        rowSize = v[0].size();
    } else {
        colSize = v[0].size() * 2;
        rowSize = v.size();
    }

    ELEM<T> elems (colSize, 0);
    VEC<T> vec (rowSize, elems);

    if (v.size() == 1) {
        if (v == w) {
            cout << "same reference" << endl;
            for (int i = 0; i < rowSize; i++) {
                vec[i][0] = v[0][i];
                vec[i][1] = v[0][i]; 
            }
        }
        else {
            for (int i = 0; i < rowSize; i++) {
                vec[i][0] = v[0][i];
                vec[i][1] = w[0][i];
            }
        }
    } else {
        int vecRow = 0, vecCol = 0;
        for (int row = 0; row < v.size(); row++) {
            for (int col = 0; col < v[0].size(); col++) {
                vec[vecRow][vecCol] = v[row][col];
                vec[vecRow][vecCol+2] = w[row][col];
                vecCol++;
            }
            vecCol = 0;
            vecRow++;
        }
    }
    return vec;
}

template <class T>
T square(int num) {
    T element = num * num;
    return element;
}

template <class T>
VEC<T> generate(int N, action_t<T> f) {

    ELEM<T> e (N, 0);
    VEC<T> vec (1, e);

    for (int i = 0; i < vec[0].size(); i++)
        vec[0][i] = f(i);

    return vec;
}

template <class T>
VEC<T> filter(VEC<T> &v, pred_t<T> f) {
    ELEM<T> e (0, 0);
    VEC<T>  res (1, e);
    bool b;
    for (int i = 0; i < v.size(); i++){
        for (int j = 0; j < v[0].size(); j++) {
            if (f(v[i][j]))
                res[0].push_back(v[i][j]);
        }
    }
    return res;

}

template <class T>
VEC<T> map(VEC<T> &v, action_t<T> f) {

    ELEM<T> e   (v[0].size(), 0);
    VEC<T>  vec (v.size(), e);

    for (int row = 0; row < v.size(); row++) {
        for (int col = 0; col < v[0].size(); col++) {
            vec[row][col] = f(v[row][col]);
        }
    }

    return vec;

}

template <class T>
ELEM<T> reduce(VEC<T> &v, map_t<T> f, ELEM<T> ident) {
    for (int row = 0; row < v.size(); row++) {
        for (int col = 0; col < v[0].size(); col++) {
            ident[0] = f(ident[0], v[row][col]);
        }
    }
    return ident;
}








/*

initVec() - takes in ELEM and makes VEC

reduce() - reduce Vector to scalar. 

generate() - takes int and gives variable of type T

zip()      - given VEC(s), create a list for index i of each VECtor
        [1, 2, 3, 4]
        [5, 6, 7, 8]

        [
            [1, 5],
            [2, 6],
            [3, 7],
            [4, 8]
                        ]

printElem() - iterate through ELEM and print each value

printVec() - print 2D Vec

filter()   - filters out all values less than 0

map()      - outputs 0 if value is <0, and 1 if value is >=0

*/






int main() {

    int abc = 1;

    cout << endl << endl;


    VEC<int> v;
    initVEC(v, ELEM<int>{1,2,3,4});
    VEC<int> w;
    initVEC(w, ELEM<int>{-1, 3, -3, 4});
    printVec(v);
    cout << string(10, '*') << endl;
    printVec(w);


    cout << string(10, '*') << endl;
    VEC<int> z = zip(v, w);
    printVec(z);


    cout << string(10, '*') << endl;
    VEC<int> x = zip(z,z);
    printVec(x);
    cout << string(10, '*') << endl;


    action_t<int> fptr = square;
    VEC<int> a = generate(10, fptr);
    printVec(a);

    
    pred_t<int> g = compare;
    VEC<int> y = filter(w,g);
    printVec(y);


    action_t<int> h = positive;
    VEC<int> u = map(w,h);
    printVec(u);


    map_t<int> k = add;
    ELEM<int> e = reduce(u,k,ELEM<int>{0});
    printElem(e);


    cout << endl << string(10, '*') << endl;
    VEC<string> ws;
    initVEC(ws, ELEM<string>{"hello","there","franco","carlacci"});
    printVec(ws);

    map_t<string> kk = add;
    ELEM<string> es = reduce(ws, kk, ELEM<string>{""});
    printElem(es);


    VEC<char> wc;
    initVEC(wc, ELEM<char>{'a','b','c','d'});
    cout << endl << string(10,'$') << endl;
    printVec(wc);

    map_t<char> nn = add;
    ELEM<char> ec = reduce(wc,nn,ELEM<char>{' '});
    cout << endl << string(10,'$') << endl;
    printElem(ec);


    return 0;

}
