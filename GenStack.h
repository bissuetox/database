#ifndef GENSTACK_H
    #define GENSTACK_H
    #include <iostream>
    #include "LinkedList.h"
    using namespace std;

    template <class T>
    class GenStack {
        private:
            DoublyLinkedList<T>* LL;
        public:
            GenStack();
            ~GenStack();

            // Core Functions
            void push(T data);
            T pop();
            T peek();

            // Helper Functions
            bool isEmpty();
            int size();
            void printStack();

    };

    // Constructor
    template <class T>
    GenStack<T>::GenStack() {
        LL = new DoublyLinkedList<T>();
    }

    // Destructor
    template <class T>
    GenStack<T>::~GenStack() {
        delete LL;
    }

    // Core Functions

    // Pushes the passed data onto the stack
    template <class T>
    void GenStack<T>::push(T data) {
        LL->insertFront(data);
    }

    // Removes and returns the top element of the stack
    template <class T>
    T GenStack<T>::pop() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty!");
        }
        else {
            return LL->removeFront();
        }
    }

    // Returns top element of the stack
    template <class T>
    T GenStack<T>::peek() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty!");
        } else {
            return LL->getFront();
        }
    }

    // Helper Functions

    // Returns bool of emptiness
    template <class T>
    bool GenStack<T>::isEmpty() {
        return LL->getSize() == 0 ? true : false;
    }

    // Returns size
    template <class T>
    int GenStack<T>::size() {
        return LL->getSize();
    }

    // Prints the stack
    template <class T>
    void GenStack<T>::printStack() {
        LL->printList(false);
    }

#endif
