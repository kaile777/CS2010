#ifndef HEADER_H
#define HEADER_H

#include <iostream>

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
void printElement(alloc a);
void printElement(range r);
int size();
void addMemory(int index, int addMemory);
void removeNode(int index);
void changeRange(int index, int subtractedMem);



template <typename T>
class List {

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
    int len = 0;

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
            if (current == tail) {
                current->next = n;
                tail = n;
                len++;
                return;
            }
            if (f(n->value, current->next->value)) {
                Node* tmp = current->next;;
                current->next = n;
                n->next = tmp;
                len++;
                return;                              // TERMINATING RETURN
            }
            current = current->next;
        }
        current->next = n;
        tail = n;
        len++;
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

        return val;
    }

    int size() const {
        return len;
    }

    // updates memory slots when merge is called for freeList
    void addMemory(int index, int addMemory) {
        Node* current = head;

        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        int newIndex, newMem;
        newIndex = index + addMemory;
        newMem   = current->value.second + addMemory;
        range r (newIndex, newMem);
        current->value = r;            
    }

    void removeNode(int index) {
        int i = 0;
        if (len == 0)
            return;
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


    void changeRange(int index, int subtractedMem) {
        if (len == 0)
            return;
        int i = 0;
        Node* current = head;
        while (i < len) {
            if (current->value.first == index) {
                current->value.first = index + subtractedMem;
                current->value.second -= subtractedMem;
                break;
            }
            current = current->next;
            i++;
        }
        

    }


};


#endif