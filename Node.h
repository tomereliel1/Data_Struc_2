#pragma once
#include <memory>
using std::shared_ptr;

template <typename T>
class Node{
private:
    int m_id;
    shared_ptr<T> m_data;
    Node* m_next;
    Node* m_previous;
public:
    Node(int id, shared_ptr<T> data);

    ~Node();

    int getId() const;

    shared_ptr<T> getData() const;

    Node<T>* getNext() const;

    Node<T>* getPrevious() const;

    void setId(int id);

    void setData(shared_ptr<T> data);

    void setNext(Node* next);

    void setPrevious(Node* previous);
};

template <typename T>
Node<T>::Node(int id, shared_ptr<T> data): m_id(id), m_data(data), m_next(nullptr), m_previous(
        nullptr) {}

template <typename T>
Node<T>::~Node() {
    m_data = nullptr;
    if (m_next != nullptr) {
        delete m_next;
    }
}

template <typename T>
int Node<T>::getId() const {
    return m_id;
}

template <typename T>
shared_ptr<T> Node<T>::getData() const {
    return m_data;
}

template <typename T>
Node<T>* Node<T>::getNext() const {
    return m_next;
}

template <typename T>
Node<T>* Node<T>::getPrevious() const {
    return m_previous;
}

template <typename T>
void Node<T>::setId(int id) {
    m_id = id;
}

template <typename T>
void Node<T>::setData(shared_ptr<T> data) {
    m_data = data;
}

template <typename T>
void Node<T>::setNext(Node<T> *next) {
    m_next = next;
}

template <typename T>
void Node<T>::setPrevious(Node<T> *previous){
    m_previous = previous;
}
