#include <iostream>
#include <time.h>

using namespace std;




// defines function to ptr that takes in two ints and returns a boolean
// points to comparison functions in this list file
template <typename T>
using comp_f = bool (*)(T, T);

// first int is the starting location, second int is the len
using range = pair<int, int>;
// first int represents the time lease
using alloc = pair<int, range>;




template <typename T>
T viewAt(int index);
template <typename T>
T removeFront();
void insertAllocList(alloc allocElement);
void dumpAlloc();
void dumpFree();
void printElement(alloc a);
void printElement(range r);
bool compare(int a, int b);
void printElement(range element);
int len();
void updateMemorylen(int index, int addMemory);
void removeNode(int index);
int size();
void mergeFreeList(List<range> &list, int reqSize)


template <typename T>
class List {

    int len = 0;

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

    int size() {
        return len;
    }

    void insertSort(T element, comp_f<T> f) {

        Node* n = new Node(element);
        Node* current = head;

        if (head == nullptr) {
            head = tail = n;
            len++;
            return;                                  // TERMINATING RETURN
        }

        if (f(n->value, current->value)) {
            n->next = current;
            head = n;
            len++;
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
                len++;
                return;                             // TERMINATING RETURN
            }
            if (current == tail) {
                current->next = n;
                tail = n;
                len++;
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


    T viewAt(int index) {
        // should implement an exception here since I cant simply "return;" since its non-void
        if (index > len || head == nullptr) {
            cout << "Index " << index << " out of bounds" << endl;
        }
        
        Node* current = head;
        for (int i = 0; i != index; i++) 
            current = current->next;

        return current->value;
    }


    T removeFront() {
        // should have exception handling for if you try deleting with an empty list
        if (head == nullptr)
            cout << "Can't remove from an empty list." << endl;

        Node* current = head;
        T val = current->value;
        head = current->next;

        delete current;

        len--;
        return val;
    }

    
    int size() const {
        return len;
    }

    void updateMemorylen(int index, int addMemory) {
        Node* current = head;
        if (index >= len) {
            cout << "Index " << index << " out of bounds" << endl;
            return;
        }
        int i = 0;
        while (1) {
            if (i == index) {
                current->value.second += addMemory;
                break;
            }
            current = current->next;
        }
    }

    void removeNode(int index) {
        int i = 0;
        if (len == 0) {
            cout << "Can't remove from empty list" << endl;
            return;
        }
            
        if (index == 0) {
            removeFront();
            return;
        }

        Node* current = head;
        while (i < index - 1) {
            current = current->next;
            i++;
        }

        Node* tmp = current->next->next;
        delete current->next;
        current->next = tmp;
        len--;

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

    range a1 (0, 10);
    range a2 (11, 5);
    range a3 (23, 10);
    range a4 (34, 3);

    
    return 0;

}