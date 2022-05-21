#ifndef LINKEDLIST_H
    #define LINKEDLIST_H
    #include "ListNode.h"
    using namespace std;

    // Doubly list class
    template <class T>
    class DoublyLinkedList{
        private:
            ListNode<T> *front;
            ListNode<T> *back;
            unsigned int size;
        public:
            DoublyLinkedList();
            ~DoublyLinkedList();

            void insertFront(T d);
            void insertBack(T d);
            T removeFront();
            T removeBack();
            T removeNode(T value);
            T getFront();
            T getBack();
            int find(T value);
            bool isEmpty();
            unsigned int getSize();
            void printList(bool isPrintLink);
    };

    template <class T>
    DoublyLinkedList<T>::DoublyLinkedList(){
        front = NULL;
        back = NULL;
        size = 0;
    }
    
    // Destructor - delete all nodes
    template <class T>
    DoublyLinkedList<T>::~DoublyLinkedList(){
        ListNode<T> *node = front;
        ListNode<T> *nodeToDelete = front;
        while (node != NULL){
            nodeToDelete = node->next;
            delete node;
            node = nodeToDelete;
        }
    }

    template <class T>
    void DoublyLinkedList<T>::insertFront(T d){
        ListNode<T> * node = new ListNode<T>(d);

        if(isEmpty()){
            front = node;
            back = node;
        }
        else{
            //it's not empty
            node->next = front;
            front->prev = node;
            front = node;
        }
        ++size;
    }

    template <class T>
    void DoublyLinkedList<T>::insertBack(T d){
        ListNode<T> *node = new ListNode<T>(d);

        if(isEmpty()){
            front = node;
            back = node;
        }
        else{
            node->prev = back;
            back->next = node;
            back = node;
        }
        ++size;
    }

    template <class T>
    T DoublyLinkedList<T>::removeFront(){
        if(isEmpty()){
            throw runtime_error("list is empty!");
        }

        ListNode<T>* temp = front;

        if(front->next == NULL){
            back = NULL;
        }
        else{
            //more than one node in the list
            front->next->prev = NULL;
        }
        front = front->next;
        temp->next = NULL;
        T data = temp->data;
        --size;
        delete temp;
        return data;
    }

    template <class T>
    T DoublyLinkedList<T>::removeBack(){
        if(isEmpty()){
            throw runtime_error("list is empty");
        }

        ListNode<T> *temp = front;

        if(back->prev == NULL){
            //only node in the list
            front = NULL;
        }
        else {
            //more than one node in the list
            back->prev->next = NULL;
        }
        back = back->prev;
        temp->prev = NULL;
        T data = temp->data;
        --size;
        delete temp;
        return data;
    }

    template <class T>
    T DoublyLinkedList<T>::getFront(){
        return front->data;
    }

    template <class T>
    T DoublyLinkedList<T>::getBack(){
        return back->data;
    }

    template <class T>
    int DoublyLinkedList<T>::find(T value){
        int pos = -1;
        ListNode<T> *curr = front;

        while(curr != NULL){
            ++pos;
            if(curr->data == value)
                break;
            
            curr = curr->next;
        }
        //checks if curr is NULL which signifies value not in Linked List
        if(curr == NULL)
            pos = -1;

        return pos;
    }

    template <class T>
    T DoublyLinkedList<T>::removeNode(T value){
        if(isEmpty()){
            throw runtime_error("Linked List is Empty!");
        }
        // Return if value isn't found
        ListNode<T> *curr = front;
        while(curr->data != value){
            curr = curr->next;
            if(curr == NULL)
                return -1;
        }

        if(curr != front && curr != back) {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        } else if(curr == front) {
            front = curr->next;
            front->prev = NULL;
        } else if(curr == back) {
            back = curr->prev;
            back->next = NULL;
        }

        curr->next = NULL;
        curr->prev = NULL;
        T data = curr->data;
        --size;
        delete curr;

        return data;   
    }

    template <class T>
    unsigned int DoublyLinkedList<T>::getSize(){
        return size;
    }

    template <class T>
    bool DoublyLinkedList<T>::isEmpty(){
        return (size == 0);
    }

    template <class T>
    void DoublyLinkedList<T>::printList(bool printLink)
    {
        ListNode<T> *curr = front;
        while(curr != 0){
        if(curr == front){
            cout << "{FRONT}: ";
        }
        else if(curr == back){
            cout << "{REAR}: ";
        }
        if(printLink)
            cout << "[ PREV: "<< curr->prev << " || " << curr->data << " || NEXT: "<< curr->next << " ] ";
        else
            cout << "[ " << curr->data << " ] ";

        curr = curr->next;
        if(curr != 0){
            cout << " <==> ";
        }
        }
        cout << endl;
    }

#endif