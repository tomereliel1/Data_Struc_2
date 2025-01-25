#pragma once
#include "Node.h"
#include "Team.h"
class ChainByRecord{
private:
    int m_size;
    Node<Team>* m_chain;
public:
    ChainByRecord();

    ~ChainByRecord();

    void add(Node<Team>* node);

    Node<Team>* remove(shared_ptr<Team> team);

    Node<Team>* getChain() const;

    int getSize () const;
};