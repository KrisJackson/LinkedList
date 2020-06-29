//
//  LinkedList.cpp
//  LinkedList
//
//  Created by Kristopher Jackson.
//  Copyright © 2020 Kristopher Jackson. All rights reserved.
//

#include <iostream>

using namespace std;

template <typename T>
class LinkedList {
    
public:
    struct Node;                                            // Node structure
    int count = 0;                                          // Total number of items in the LL
    
    bool empty();                                           // Checks if list is empty
    void dropLast();                                        // Removes the last item in the LL
    void dropFirst();                                       // Removes the last item in the LL
    void push(T data);                                      // Adds an item to the front of the LL
    void append(T data);                                    // Adds an item to the back of the LL
    bool exist(int index);                                  // Return true if item exists at index
    void remove(int atIndex);                               // Removes an item at a zero-based index if possible
    void add(T data, int atIndex);                          // Adds an item at a zero-based index if possible
    void iterate(void(*f)(Node), bool reversed = false);    // Called if client wants to perform a task on every node
    
    ~LinkedList() {                                         // Deconstructor
        for (Node* p = head; p != NULL; p = p->next)
            delete p->prev;
        delete tail;
    };
    
private:
    LinkedList::Node* head = NULL;                          // First element in the LL
    LinkedList::Node* tail = NULL;                          // Last element in the LL
    
};


// Node implementation
template <typename T>
struct LinkedList<T>::Node {
    
public:
    T data = NULL;          // Data being stored
    Node* next = NULL;      // Pointer to the next element
    Node* prev = NULL;      // Pointer to the previous element
};


// Checks if list is empty
template <typename T>
bool LinkedList<T>::empty() {
    return count == 0;
};


// Removes the last item in the LL
template <typename T>
void LinkedList<T>::dropLast() {
    
    if (count == 0) { return; }
    
    if (count == 1) {
        head = NULL;
        tail = NULL;
        count--;
        return;
    }
    
    tail = tail->prev;
    tail->next = NULL;
    count--;
    
};


// Removes the first item in the LL
template <typename T>
void LinkedList<T>::dropFirst() {
    
    if (count == 0) { return; }
    
    if (count == 1) {
        head = NULL;
        tail = NULL;
        count--;
        return;
    }
    
    head = head->next;
    head->prev = NULL;
    count--;
    
};


// Return true if item exists at index
template <typename T>
bool LinkedList<T>::exist(int index) {
    return index < count;
};


// Adds an item to the front of the LL
template <typename T>
void LinkedList<T>::push(T data) {
    Node* node = new Node;
    node->data = data;

    if (head == NULL) {
        
        head = node;
        tail = node;
        
    } else {
        
        head->prev = node;
        node->next = head;
        head = node;
        
    }
    
    count++;
};


// Adds an item to the back of the LL
template <typename T>
void LinkedList<T>::append(T data) {
    Node* node = new Node;
    node->data = data;

    if (head == NULL) {
        
        head = node;
        tail = node;
        
    } else {
        
        tail->next = node;
        node->prev = tail;
        tail = node;
        
    }
    
    count++;
};


// Adds an item at a zero-based index if possible
template <typename T>
void LinkedList<T>::add(T data, int atIndex) {
    
    // Fatal error if index out of range
    if (atIndex > count) {
        cout << "Index out of bounds.";
        abort();
    }
    
    if (atIndex == 0) {

        push(data);
        
    } else if (atIndex == count) {
        
        append(data);
        
    } else {
    
        Node* node = new Node;
        node->data = data;
        
        Node* p = head;
        for (int i = 0; i < atIndex - 1; i++) 
            p = p->next;

        node->next = p->next;
        p->next = node;
        node->next->prev = node;
        node->prev = p;
        
    }
    
    count++;
};


// Removes an item at a zero-based index if possible
template <typename T>
void LinkedList<T>::remove(int atIndex) {
    
    // Fatal error if index out of range
    if (!exist(atIndex)) {
        cout << "Index out of bounds.";
        abort();
    }
    
    if (atIndex == 0 || count == 1) {

        dropFirst();
        
    } else if (atIndex == (count - 1)) {
        
        dropLast();
        
    } else {
    
        Node* p = head;
        for (int i = 0; i < atIndex; i++)
            p = p->next;

        p->prev->next = p->next;
        p->next->prev = p->prev;
        
    }
    
    count--;
};


// Called if client wants to perform a task on every node
template <typename T>
void LinkedList<T>::iterate(void (*f)(Node), bool reversed) {

    if (reversed) {
        for (Node* p = tail; p != NULL; p = p->prev)
            (*f)(*p);
    } else {
        for (Node* p = head; p != NULL; p = p->next)
            (*f)(*p);
    }
    
};
