#ifndef LINKED_LIST_H
#define LINKED_LIST_H

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    void push_front(int value);
    void push_back(int value);
    void pop_front();
    void pop_back();
    bool empty() const;
    void print() const;

private:
    struct Node
    {
        int data;
        Node *next;
        Node(int val) : data(val), next(nullptr) {}
    };
    Node *head;
    Node *tail;
};

#endif // LINKED_LIST_H
