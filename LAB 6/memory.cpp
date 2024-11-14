#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "header.h"

using namespace std;

int verifyRequest(List<range> &list, int memSize);
void mergeFreeList(List<range> &list);
void freeToAlloc(int index, int memSize, int expiry);
bool compare(range a, range b);
bool compare(alloc a, alloc b);
void logRequest(int expiry, int index, int size);
void debug();


List<range> freeList;
List<alloc> allocList;

comp_f<alloc> fa = compare;
comp_f<range> ff = compare;

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
int total_requests = 0;



void printElement(range r) {
    cout << "[" << r.first << "]" << ", (" << r.second << ")";
    cout << endl;
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
    returns true if lease expiry in 'a' is less than lease expiry in b
*/
bool compare(alloc a, alloc b) {
    if (a.first < b.first) 
        return true;
    return false;
}


// check if any memory sizes in freeList are immediately large enough
// to satisfy requests
// return index of freeList block where there was a suitable space
// merge if unsatisfied. If after merge, still unsatisfied, return (-1)
int verifyRequest(List<range> &free, int memSize) {

    for (int i = 0; i < free.size(); i++) {
        if (free.viewAt(i).second >= memSize)  
            return free.viewAt(i).first;
    }

    // call merge of freeList
    mergeFreeList(free);

    for (int i = 0; i < free.size(); i++) {
        if (free.viewAt(i).second >= memSize)  
            return free.viewAt(i).first;
    }

    return -1;
    
}


/*
    performed reduction that takes in additive function until reqSize is met
*/
void mergeFreeList(List<range> &list) {

    if (list.size() == 0 || list.size() == 1)
        return;
    
    for (int i = 0; i < list.size(); i++) {
        if (i + 1 < list.size()) {
            if (list.viewAt(i).first + list.viewAt(i).second == list.viewAt(i+1).first + 1) {
                
                int size = list.viewAt(i+1).second;
                list.addMemory(list.viewAt(i).first, size);
                
                // remove ith node in list
                list.removeNode(i+1);
            }
        }
    }
}

/*
    Adds memory to allocList and removes same memory from freeList.
    'fa' in inserSort function call is the pointer to the function compare
    that compares alloc types.
*/
void freeToAlloc(int index, int memSize, int expiry) {
    range r (index, memSize);
    alloc a (expiry, r);
    allocList.insertSort(a, fa);

    freeList.changeRange(index, memSize);
}

void logRequest(int expiry, int index, int size) { 
    cout << "Entry :  ";
    cout << "@" << expiry << " | ";
    cout << "[" << index << "], (";
    cout << size << ")";
    cout << "   VERIFIED: ";
    (index>=0) ? cout << "Y" : cout << "N";
    cout << endl;
}


void debug() {
    cout << endl;
    cout << endl << "Free List" << endl;
    freeList.printList();
    cout << endl << "Alloc List" << endl;
    allocList.printList();
    cout << "-----------" << endl;
}



int main() {

    
    srand(time(NULL));

    
    range r (0, 1000);
    freeList.insertSort(r, ff);

    int clock_tick = 0;

    while (clock_tick != TIME_LIMIT) {
        
        /*
            Check if lease expiries are due in allocList.
            If so, remove from alloc list and insert back into freeList.
        */
        // views first pair element in first allocList entry
        int index = 0;

        int leaseExpiry;

        if (allocList.size() != 0) {

            leaseExpiry = allocList.viewAt(index).first;

            while (leaseExpiry == clock_tick) {

                // check lease expiry of next element in list if there is one
                leaseExpiry = allocList.viewAt(index).first;

                // val is equal to the range in the alloc type value
                range val = allocList.viewAt(index).second;
                // inserts deallocated memory into freeList
                freeList.insertSort(val, ff);
                // deallocate memory values from allocList
                allocList.removeFront();

                // increment index to check for more lease expiries
                index++;

                // check that the list is not empty. If it is, break;
                if (allocList.size() == 0)
                    break;
                
                

            }
        }
            

        


        // check if any MemoryRequests need to be made:
        if (clock_tick % 10 == 0) {
            // make memory request using random lease time and memory size
            int expiryTime = (rand() % (MAX_LEASE - MIN_LEASE) + MIN_LEASE) + clock_tick;
            int memSize    = (rand() % (MAX_SIZE - MIN_SIZE) + MIN_SIZE);

            // verify request in freeList. If not satisfied, merge holes into 
            // size needed
            // if verified >= 0, satisfied request, else if -1 unsatisfied
            int verified = verifyRequest(freeList, memSize);
            logRequest(expiryTime, verified, memSize);
            if (verified >= 0) {
                freeToAlloc(verified, memSize, expiryTime);
                total_requests++;
                debug();
            }
            else {
                unsatisfied_requests++;
                debug();
            }

        }

        clock_tick++;

    }

    cout << endl;
    cout << "Free List:" << endl;
    freeList.printList();
    cout << endl;

    cout << "Alloc List:" << endl;
    allocList.printList();
    cout << endl;

    cout << "UNSATISFIED REQUESTS : " << unsatisfied_requests << endl;
    cout << "TOTAL REQUESTS       : " << total_requests << endl;


    return 0;



}

