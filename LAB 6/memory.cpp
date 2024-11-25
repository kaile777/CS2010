#include <iostream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

using range = pair<int, int>;
using alloc = pair<int, range>;

// #define DEBUG

vector<range> freeList;
vector<alloc> allocList;


void printElement(range r);
void printElement(alloc a);
void insertFreeList(range element);
void insertAllocList(alloc element);
void mergeFreeList();
int verifyRequest(int memSize);
void transferAllocToFree(alloc a);
void transferFreeToAlloc(alloc a);
void debug();
void logRequest(int expiry, int index, int size);




int clock_tick;

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
int satisfied_requests = 0;
int total_requests;

int meanMemSize = 0;
int meanLeaseSize = 0;

int largestMemSize = MIN_SIZE - 1;
int smallestMemSize = MAX_SIZE + 1;
int largestLeaseSize = MIN_LEASE - 1;
int smallestLeaseSize = MAX_LEASE + 1;

double satisfiedReqRate;

void debug() {

    cout << "------------------------" << endl;
    cout << "Free List:" << endl;
    for (range element : freeList) {
        printElement(element);
    }
    cout << "---" <<endl;
    cout << "Alloc List:" << endl;
    for (alloc element : allocList) {
        printElement(element);
    }
    cout << "------------------------" << endl;
}

void printElement(range r) {
    cout << "[" << r.first << "]" << ", (" << r.second << ")";
    cout << endl;
}

void printElement(alloc a) {
    cout << "@" << a.first << " , ";
    cout << "[" << a.second.first << "], ";
    cout << "(" << a.second.second << ")" << endl;
}



/*
    Iterates through freeList from END to START, comparing the indices of each element in the list.
    Inserts indexes so that lowest index is toward beggining of vector, and greatest is in back of vector
    After each element is inserted, merge changes are also made if neccessary.
*/
void insertFreeList(range element) {
    freeList.push_back(element);
    for (int i = freeList.size() - 1; i > 0; i--) {
        if (i == 0) break;
        if (freeList[i].first < freeList[i-1].first) {
            range tmp = freeList[i-1];
            freeList[i-1] = freeList[i];
            freeList[i] = tmp;
        }
    }
    mergeFreeList();
}

/*
    Iterates through allocList from END to START, comparing the lease expiries of each element in the list.
    Inserts elements so that nearest expiry is toward end of vector for easy pops, and greatest is in beggining of vector.
    Merge changes not neccessary for allocList.
*/
void insertAllocList(alloc element) {
    allocList.push_back(element);
    for (int i = allocList.size() - 1; i > 0; i--) {
        if (i == 0) break;
        if (allocList[i].first > allocList[i-1].first) {
            alloc tmp = allocList[i-1];
            allocList[i-1] = allocList[i];
            allocList[i] = tmp;
        }
    }
}   

/*
    Any fragmented memory chunks are joined together to create larger blocks.
*/
void mergeFreeList() {
    int i = 0;
    while (i < freeList.size()) {
        // delete any blocks that have memSize of zero.
        // continue to prevent incrementing i.
        if (freeList[i].second == 0) {
            freeList.erase(freeList.begin() + i);
            continue;
        }

        // if the next chunk is contiguous then merge the two blocks together
        if (i + 1 < freeList.size() && freeList[i].first + freeList[i].second == freeList[i + 1].first) {
            freeList[i].second += freeList[i + 1].second;
            freeList.erase(freeList.begin() + i + 1);
        } else {
            // increment i if no changes are made.
            ++i;
        }
    }
}


/*
    Iterate through entire freeList. If at any point a free block exists that meets the size requirment,
    return the index of the memory block.
    If after the whole freeList has been iterated over and no return has been made, return -1 to 
    signify an unsatisfied request.
*/
int verifyRequest(int memSize) {
    for (range element : freeList) {
        if (element.second >= memSize)
            return element.first;
    }
    return -1;
}

void transferAllocToFree(alloc a) {
    int index = a.second.first;
    int size = a.second.second;
    range r (index, size);
    insertFreeList(r);
    allocList.pop_back();
}

void transferFreeToAlloc(alloc a) {
    int index = a.second.first;
    int size = a.second.second;
    for (int i = 0; i < freeList.size(); i++) {
        if (freeList[i].first == index) {
            if (freeList[i].first == 0)
                freeList[i].first += size;
            else
                freeList[i].first += size;
            freeList[i].second -= size;
        }
    }
    mergeFreeList();
    insertAllocList(a);
}

void logRequest(int expiry, int index, int size) { 
    cout << endl << "Entry :  ";
    cout << "@" << expiry << " | ";
    cout << "[" << index << "], (";
    cout << size << ")";
    cout << "   VERIFIED: ";
    (index >= 0) ? cout << "Y" : cout << "N";
    cout << endl;
}


int main() {

    srand(time(NULL));

    clock_tick = 0;

    // initialize freeList with a size of MEMORY_SIZE
    range r (0, 1000);
    freeList.push_back(r);


    while (clock_tick <= TIME_LIMIT) {

        #ifdef DEBUG
        cout << "CLOCK: " << clock_tick << endl;
        #endif

        // check and remove lease expiries
        if (allocList.size() != 0) {  
            int end = allocList.size() - 1;
            while (allocList[end].first == clock_tick) {
                #ifdef DEBUG
                cout << "EXPIRY: " << endl;
                printElement(allocList[end]);
                cout << endl;
                #endif
                transferAllocToFree(allocList[end]);
                #ifdef DEBUG
                debug();
                #endif
                end--;
            }
        }

        // make memory request every 10 ticks in clock cycle
        // check if any MemoryRequests need to be made:
        if (clock_tick % 10 == 0) {
            // make memory request using random lease time and memory size
            int expiryTime = (rand() % ((MAX_LEASE+1) - MIN_LEASE) + MIN_LEASE) + clock_tick;
            int memSize    = (rand() % ((MAX_SIZE+1) - MIN_SIZE) + MIN_SIZE);

            /*
                Verify if request can be satisfied in the freeList.
                'verified' boolean value will hold value of index of free memory,
                or -1 if a request cannot be made.
            */ 
            int verified = verifyRequest(memSize);

            if (memSize < smallestMemSize)
                smallestMemSize = memSize;
            if (memSize > largestMemSize)
                largestMemSize = memSize;
            if ((expiryTime - clock_tick) < smallestLeaseSize)
                smallestLeaseSize = (expiryTime - clock_tick);
            if ((expiryTime - clock_tick) > largestLeaseSize)
                largestLeaseSize = (expiryTime - clock_tick);

            meanMemSize += memSize;
            meanLeaseSize += expiryTime - clock_tick;

            if (verified >= 0) {
                range r (verified, memSize);
                alloc a (expiryTime, r);
                transferFreeToAlloc(a);

                satisfied_requests++;

                #ifdef DEBUG
                logRequest(expiryTime, verified, memSize);
                debug();
                #endif
            } else {
                #ifdef DEBUG
                logRequest(expiryTime, verified, memSize);
                #endif
                unsatisfied_requests++;
            }

        }

        clock_tick++;
        
    }

    total_requests = satisfied_requests + unsatisfied_requests;
    meanMemSize = meanMemSize / total_requests;
    meanLeaseSize = meanLeaseSize / total_requests;
    satisfiedReqRate = ((double)satisfied_requests / (double)total_requests) * 100.0;

    cout << endl << "**********";
    cout << endl << "STATISTICS" << endl;
    cout <<         "**********" << endl;
    cout << "Satisfied Requests   : " << satisfied_requests << endl;
    cout << "Unsatisfied Requests : " << unsatisfied_requests << endl;
    cout << "TOTAL Requests       : " << total_requests << endl << endl;
    cout << "Request Fulfillment Rate : " << satisfiedReqRate << "%" << endl;
    cout << endl;
    cout << "Largest Memory Size Requested  : " << largestMemSize << endl;
    cout << "Smallest Memory Size Requested : " << smallestMemSize << endl;
    cout << "MEAN Memory Size Requested     : " << meanMemSize << endl;
    cout << endl;
    cout << "Largest Lease Size Requested  : " << largestLeaseSize << endl;
    cout << "Smallest Lease Size Requested : " << smallestLeaseSize << endl;
    cout << "MEAN Lease Size Requested     : " << meanLeaseSize << endl;
    cout << endl;

    debug();

    return 0;

}