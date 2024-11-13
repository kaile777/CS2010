#include <iostream>
#include <time.h>

using namespace std;




// defines function to ptr that takes in two ints and returns a boolean
// points to comparison functions in this list file
template <typename T>
using comp_f = bool (*)(T, T);

// first int is the starting location, second int is the size
using range = pair<int, int>;
// first int represents the time lease
using alloc = pair<int, range>;

void insertAllocList(alloc allocElement);
void dumpAlloc();
void dumpFree();
void printElement(alloc a);
void printElement(range r);
bool compare(int a, int b);
void printElement(range element);


template <typename T>
class List {

    int size = 0;

    class Node {
    
    public:
        Node* next;
        T value;

        Node() {
            value = NULL;
            next  = nullptr;
        }

        Node(T val) {
            value = val;
            next = nullptr;
        }
    };

private:

    Node* head;
    Node* tail;

public:

    List() {
        head = nullptr;
        tail = nullptr;
    }

    void insertSort(T element, comp_f<T> f) {

        Node* n = new Node(element);
        Node* current = head;

        if (head == nullptr) {
            head = tail = n;
            return;                                  // TERMINATING RETURN
        }

        if (f(n->value, current->value)) {
            n->next = current;
            head = n;
            size++;
            return;
        }
        
        while (current->next != nullptr) {
            if (f(n->value, current->next->value)) {
                if (current == tail) {
                    current->next = n;
                    tail = n;
                }
                else {
                    Node* tmp = current->next;;
                    current->next = n;
                    n->next = tmp;
                }
                size++;
                return;                             // TERMINATING RETURN
            }
            if (current == tail) {
                current->next = n;
                tail = n;
                size++;
                return;
            }
            current = current->next;
        }

        current->next = n;
        tail = n;
        
    }



    void printList() {
        if(head == nullptr) 
            cout << "Empty List";          

        Node* current = head;
        while (current != nullptr) {
            printElement(current->value);
            current = current->next;
        }
    }


};


bool compare(range a, range b) {
    return a.first < b.first;
}

void printElement(range element) {
    cout << element.first << " ";
    cout << element.second << endl;
}


int main() {


    comp_f<range> f = compare;

    srand(time(NULL));

    

    List<range> list;

    for (int i = 0; i < 25; i++) {
        int num = 0 + (rand() % (10000 - 0 + 1));
        range r (num, num);
        list.insertSort(r, f);
    }

    list.printList();


    return 0;


}