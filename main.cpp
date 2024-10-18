// COMSC-210 | Midterm #1 | Nina Tsao

#include <iostream>     // for input and output
using namespace std;    // using this to instead writing std:: in every input and output line

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// create a doubly linked list class
class DoublyLinkedList {
private:
    struct Node {   // define a struct node
        int data;
        Node* prev; // pointer to previous node
        Node* next; // pointer to next node

        // initialize the node
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node* head;     // pointer to the head node
    Node* tail;     // pointer to the tail node

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }  // initialize the doubly linked list

    // insert node after the position
    void insert_after(int value, int position) {
        if (position < 0) {     // check if position is equal or greater than 0
            cout << "Position must be >= 0." << endl;   // printout the message if the position is less than 0
            return;     // exit the function
        }

        Node* newNode = new Node(value);    // create a new node with value

        if (!head) {    // if head is empty
            head = tail = newNode;  // set head and tail to newNode
            return;     // exit the function
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)  // traverse to the position
            temp = temp->next;      // move to the next node
        if (!temp) {    // if temp is empty
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;     // exit the function
        }

        newNode->next = temp->next; // make new node next to the temp(current) node next to connect
        newNode->prev = temp;   // make new node prev to the temp(current) node to connect

        if (temp->next)     // if temp(current) next node is not empty
            temp->next->prev = newNode;     // set (temp(current) next)'s previous to the newNode
        else
            tail = newNode; // if temp(current) next node is empty, set the tail to the newNode

        temp->next = newNode;
    }

    // delete the value
    void delete_val(int value) {
        if (!head) return;      // if head is empty
            Node* temp = head;

        // traverse to find the value
        while (temp && temp->data != value)
            temp = temp->next;  // move to the next node

        if (!temp) return;  // if temp(value) is empty

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;
        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;
        delete temp;
    }

    // delete the node at a position
    void delete_pos(int pos) {
        if (!head) {        // if head is empty
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1) {
            pop_front();    // call the function
            return;
        }

        Node* temp = head;
        for (int i = 1; i < pos; i++){  // traverse to the position
            if (!temp) {    // if the position does not exist
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;  // move to the next node
        }

        if (!temp) {    // if the position doesn't exist (over the size)
            cout << "Position doesn't exist." << endl;
            return;
        }
        if (!temp->next) {  // if temp next is empty (tail)
            pop_back(); // call the function
            return;
        }

        // reroute the nodes
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;

        delete temp;
    }

    void push_back(int v) {     // add node to the back
        Node* newNode = new Node(v);
        if (!tail)  // if tail is empty
            head = tail = newNode;  // set head and tail to the newNode
        else {
            tail->next = newNode;   // make tail next to the newNode
            newNode->prev = tail;   // make newNode prev to the tail
            tail = newNode;     // update
        }
    }

    void push_front(int v) {    // add node to the front
        Node* newNode = new Node(v);
        if (!head)  // if head is empty
            head = tail = newNode;  // set head and tail to the newNode
        else {
            newNode->next = head;   // make newNode next to the head
            head->prev = newNode;   // make head prev to the newNode
            head = newNode;     // update
        }
    }

    void pop_front() {  // remove the first node
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = head;
        if (head->next) {   // if head next is not empty
            head = head->next;  // move to the next
            head->prev = nullptr;   // and set the previous one to null
        }
        else
            head = tail = nullptr;  // set head and tail to null

        delete temp;    // free the memory
    }

    void pop_back() {   // remove the last node
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;
        if (tail->prev) {   // if tail prev is not empty
            tail = tail->prev;  // move to the previous
            tail->next = nullptr;   // and set the one we changed to null
        }
        else
            head = tail = nullptr;  // set head and tail to null
        
        delete temp;    // free the memory
    }

    // destructor to cleanup
    ~DoublyLinkedList() {
        while (head) {  // if the list is not empty
            Node* temp = head;
            head = head->next;  // move head to the next
            delete temp;
        }
    }

    void print() {  // prinout the whole list
        Node* current = head;
        if (!current) {     // if list is empty
            cout << "List is empty." << endl;
            return;
        }

        while (current) {   // while list is not empty
            cout << current->data << " ";   // printout the current node data
            current = current->next;    // move to the next node
        }

        cout << endl;
    }

    void print_reverse() {  // printout the whole list from the back to the front
        Node* current = tail;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS; // dummy statement to avoid compiler warning
    
    return 0;
}