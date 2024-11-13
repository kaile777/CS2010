#ifndef HEADER_H
#define HEADER_H

#include <iostream>

using namespace std;

// defines function to ptr that takes in two ints and returns a boolean
// points to comparison functions in this list file
template <typename T>
using comp_f = bool (*)(T, T);

// first int is the starting location, second int is the size
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
        size++;
        
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
        if (index > size || head == nullptr) {
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

        return val;
    }


};


#endif