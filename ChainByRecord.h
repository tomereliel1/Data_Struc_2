#pragma once
#include "Node.h"
#include "Team.h"
class ChainByRecord{
private:
    int m_record;
    int m_size;
    Node<Team>* m_chain;
public:
    explicit ChainByRecord(int record);

    ~ChainByRecord();

    void add(Node<Team>* node);

    Node<Team>* remove(shared_ptr<Team> team);

    Node<Team>* getChain() const;

    int getSize () const;
};