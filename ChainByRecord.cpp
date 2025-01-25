#include "ChainByRecord.h"
ChainByRecord::ChainByRecord(): m_size(0), m_chain(nullptr) {}

ChainByRecord::~ChainByRecord() {
    if (m_chain != nullptr){
        delete(m_chain);
    }
}


void ChainByRecord::add(Node<Team> *node) {
    if (m_chain != nullptr){
        m_chain->setPrevious(node);
    }
    node->setNext(m_chain);
    m_chain = node;
    m_size++;
}

Node<Team>* ChainByRecord::remove(shared_ptr<Team> team) {
    Node<Team>* removedNode = team->getRecordNode();
    Node<Team>* nextNode = removedNode->getNext();
    Node<Team>* preNode = removedNode->getPrevious();
    if (nextNode != nullptr){
        nextNode->setPrevious(preNode);
    }
    if (m_chain == removedNode){
        m_chain = nextNode;
    } else {
        preNode->setNext(nextNode);
    }
    removedNode->setNext(nullptr);
    removedNode->setPrevious(nullptr);
    m_size--;
    return removedNode;
}

Node<Team>* ChainByRecord::getChain() const {
    return m_chain;
}
 int ChainByRecord::getSize() const {
    return m_size;
}