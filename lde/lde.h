#ifndef LDE_H
#define LDE_H

#include <iostream>

template <class T>
class lde
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node *prev;

        Node(const T &data, Node *next = nullptr, Node *prev = nullptr) : data(data), next(next), prev(prev) {}
    };

    Node *head;
    Node *tail;
    size_t cont;

public:
    lde();
    ~lde();

    bool isempty();

    void pushfront(const T &data);
    void pushback(const T &data);

    size_t size();

    lde &operator<<(const T &data)
    {
        pushback(data);
        return *this;
    }

    lde &operator<=(const T &data)
    {
        pushfront(data);
        return *this;
    }
};

template <class T>
lde<T>::lde()
{
    head = nullptr;
    tail = nullptr;
    cont = 0;
}

template <class T>
lde<T>::~lde()
{
    // :o
}

template <class T>
bool lde<T>::isempty()
{
    return cont == 0;
}

template <class T>
void lde<T>::pushback(const T &data)
{
    Node *node = new Node(data, nullptr, tail);
    if (cont == 0)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->next = node;
        tail = node;
    }
    cont++;
}

template <class T>
void lde<T>::pushfront(const T &data)
{
    Node *node = new Node(data, head);
    if (cont == 0)
    {
        head = node;
        tail = node;
    }
    else
    {
        head->prev = node;
        head = node;
    }
    cont++;
}

template <class T>
inline size_t lde<T>::size()
{
    return cont;
}

#endif // LDE_H
