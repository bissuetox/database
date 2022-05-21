#ifndef LISTNODE_H
#define LISTNODE_H

#include <iostream>
#include <exception>
using namespace std;

template <class T> class ListNode{
    public:
        ListNode();
        ListNode(T d);
        ~ListNode();
        ListNode *next;
        ListNode *prev;
        T data;
};

// Constructors
template <class T> ListNode<T>::ListNode(){}

template <class T> ListNode<T>::ListNode(T d){
    data = d;
    next = NULL;
    prev = NULL;
}

template <class T> ListNode<T>::~ListNode(){
    // Linked List takes care of these
    if (next) delete next;
    if (prev) delete prev;
    // delete next;
    // delete prev;
}

#endif