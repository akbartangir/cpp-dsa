#include "../../include/linked_list.h"
#include <iostream>

LinkedList::LinkedList() : head(nullptr), tail(nullptr) {}

LinkedList::~LinkedList()
{
    while (!empty())
    {
        pop_front();
    }
}

void LinkedList::push_front(int value)
{
    Node *new_node = new Node(value);
    new_node->next = head;
    head = new_node;
    if (!tail)
        tail = head;
}

void LinkedList::push_back(int value)
{
    Node *new_node = new Node(value);
    if (tail)
    {
        tail->next = new_node;
        tail = new_node;
    }
    else
    {
        head = tail = new_node;
    }
}

void LinkedList::pop_front()
{
    if (!head)
        return;
    Node *temp = head;
    head = head->next;
    delete temp;
    if (!head)
        tail = nullptr;
}

void LinkedList::pop_back()
{
    if (!head)
        return;
    if (head == tail)
    {
        delete head;
        head = tail = nullptr;
        return;
    }
    Node *curr = head;
    while (curr->next != tail)
    {
        curr = curr->next;
    }
    delete tail;
    tail = curr;
    tail->next = nullptr;
}

bool LinkedList::empty() const
{
    return head == nullptr;
}

void LinkedList::print() const
{
    Node *curr = head;
    while (curr)
    {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}
