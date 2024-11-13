#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "header.h"

using namespace std;

// global constant variables
const int MIN_LEASE = 40;
const int MAX_LEASE = 70;
const int MIN_SIZE  = 50;
const int MAX_SIZE  = 350;
const int TIME_LIMIT = 1000;
const int REQUEST_INTERVAL = 10;
const int MEMORY_SIZE = 1000;

// global mutable variables
int unsatisfied_requests = 0;



void printElement(range r) {
    cout << "[" << r.first << "]" << ", (" << r.second << ")";
}

void printElement(alloc a) {
    cout << "~" << a.first << "~ , ";
    cout << "[" << a.second.first << "], ";
    cout << "(" << a.second.second << ")" << endl;
}



/*
    call this function when comparing two elements in freeList
    returns true if range a < b
    - compares starting index
    - returns true if starting index of a is less than starting index of b
*/
bool compare(range a, range b) {
    if (a.first < b.first)
        return true;
    return false;
}

/*
    call this function when comparing two elements in allocList
    returns true if lease expiry in a is less than lease expiry in b
*/
bool compare(alloc a, alloc b) {
    if (a.first < b.first) 
        return true;
    return false;
}



int main() {

    
    comp_f<alloc> fa = compare;

    List<alloc> allocList;

    range p (0, 50);
    alloc a (70, p);
    allocList.insertSort(a, fa);

    range p2 (51, 100);
    alloc a2 (50, p2);
    allocList.insertSort(a2, fa);


    
    allocList.printList();




    return 0;
}

