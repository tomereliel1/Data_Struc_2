#pragma once
#include <memory>
#include "Node.h"
using std::shared_ptr;
using std::make_shared;


class Team {
private:
    int m_id;
    int m_teamsNum;
    int m_record;
    shared_ptr<Team> m_parent;
    Node<Team> * m_recordNode;

public:
    explicit Team(int id);

    ~Team();

    void setParent(shared_ptr<Team> team);

    void setId(int id);

    void setRecordNode(Node<Team>* node);

    void addTeamsNum(int teamsNum);

    void addRecord(int record);

    void updateVictory();

    void updateLoss();

    int getRecord() const;

    int getTeamsNum() const;

    int getId() const;

    shared_ptr<Team> getParent() const;

    shared_ptr<Team> getRoot();

    Node<Team>* getRecordNode() const;
};