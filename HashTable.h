#include "Node.h"

template <typename T>
class HashTable{
private:
    int m_size;
    int m_keysNum;
    Node<T>** m_arr;

    int fixKey(int key);

    void insertToArr(Node<T>* node);
public:
    HashTable();

    ~HashTable();

    Node<T>* find(int key);

    void insert(Node<T>* node);

    void remove(int key);

};

template <typename T>
HashTable<T>::HashTable(): m_size(2), m_keysNum(0) {
    m_arr = new Node<T>*[2]();
    m_arr[0] = nullptr;
    m_arr[1] = nullptr;
}

template <typename T>
HashTable<T>::~HashTable() {
    for (int i = 0; i < m_size; ++i) {
        delete(m_arr[i]->getData());
    }
}

template <typename T>
Node<T>* HashTable<T>::find(int key) {
    int newKey = fixKey(key);
    if (m_arr[newKey] == nullptr){
        return nullptr;
    } else {
        Node<T>* currentNode = m_arr[newKey];
        while (currentNode != nullptr){
            if (currentNode->getId() == key) {
                return currentNode;
            }
            currentNode = currentNode->getNext();
        }
        return nullptr;
    }
}

template <typename T>
void HashTable<T>::insert(Node<T> *node) {
    int key = node->getId();
    if (this->find(key) != nullptr){
        return;
    } else if (m_keysNum + 1 == m_size / 2) {
        int oldSize = m_size;
        m_size = 2 * oldSize;
        Node<T>** newArr = new Node<T> *[m_size]();
        Node<T>** temp = m_arr;
        m_arr = newArr;
        for (int i = 0; i < m_size; i++) {
            newArr[i] = nullptr;
        }
        for (int i = 0; i < oldSize; i++) {
            Node<T> *current = temp[i];
            while (current != nullptr) {
                Node<T> *next = current->getNext();
                current->setNext(nullptr);
                insertToArr(current);
                current = next;
            }
        }
        delete [] temp;
    }
    insertToArr(node);
    m_keysNum++;
}

template <typename T>
void HashTable<T>::remove(int key){
    int newKey = fixKey(key);
    Node<T>* removedNode = m_arr[newKey];
    if (removedNode == nullptr){
        return;
    } else if (removedNode->getId() == key){
        m_arr[newKey] = removedNode->getNext();
        removedNode->setNext(nullptr);
        //////////////////////////////removedNode->setData(nullptr);
        delete removedNode;
        m_keysNum--;
        return;
    } else {
        Node<T> *currentNode = removedNode;
        while (removedNode != nullptr) {
            if (removedNode->getId() == key) {
                currentNode->setNext(removedNode->getNext());
                removedNode->setNext(nullptr);
                ///////////////////removedNode->setData(nullptr);
                delete removedNode;
                m_keysNum--;
                return;
            }
            else {
                currentNode = removedNode;
                removedNode = removedNode->getNext();
            }
        }
        return;
    }
}

template <typename T>
int HashTable<T>::fixKey(int key) {
    key = key % m_size;
    if (key < 0){
        key += m_size;
    }
    return key;
}

template <typename T>
void HashTable<T>::insertToArr(Node<T> *node) {
    int newKey = fixKey(node->getId());
    if (m_arr[newKey] == nullptr){
        m_arr[newKey] = node;
        //return node;
    } else {
        node->setNext(m_arr[newKey]);
        m_arr[newKey] = node;
        //return node;
    }
}
