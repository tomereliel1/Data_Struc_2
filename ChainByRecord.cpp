#include "ChainByRecord.h"

ChainByRecord::ChainByRecord(int record): m_record(record),m_size(0), m_chain(nullptr) {}

void ChainByRecord::add(Node<Team> *node) {
    node->setNext(m_chain);
    m_chain = node;
    m_size++;
}

Node<Team>* ChainByRecord::remove(int id) {
    Node<Team>* removedNode = nullptr;
    if (m_chain->getId() == id){
        removedNode = m_chain;
        m_chain = m_chain->getNext();
        removedNode->setNext(nullptr);
        m_size--;
        return removedNode;
    } else {
        Node<Team>* currentNode = m_chain;
        removedNode = m_chain->getNext();
        while (removedNode != nullptr){
            if (removedNode->getId() == id){
                currentNode->setNext(removedNode->getNext());
                removedNode->setNext(nullptr);
                m_size--;
                return removedNode;
            } else {
                currentNode = removedNode;
                removedNode = removedNode->getNext();
            }
        }
        return removedNode;
    }
}