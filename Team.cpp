#include "Team.h"

Team::Team(int id):m_id(id), m_teamsNum(1) , m_record(0), m_parent(nullptr), m_recordNode(nullptr){
}

Team::~Team(){
    m_parent = nullptr;
}

void Team::setId(int id) {
    m_id = id;
}

void Team::setParent(shared_ptr<Team> team) {
    m_parent = team;
}

void Team::setRecordNode(Node<Team> *node) {
    m_recordNode = node;
}

void Team::updateVictory() {
    m_record++;
}

void Team::updateLoss() {
    m_record--;
}

int Team::getRecord() const {
    return m_record;
}

int Team::getTeamsNum() const {
    return m_teamsNum;
}

int Team::getId() const {
    return m_id;
}



void Team::addTeamsNum(int teamsNum) {
    m_teamsNum += teamsNum;
}

void Team::addRecord(int record) {
    m_record += record;
}



shared_ptr<Team> Team::getParent() const {
    return m_parent;
}

shared_ptr<Team> Team::getRoot() {
    if (m_parent != nullptr){
        if (m_parent->m_parent == nullptr){
            return m_parent;
        } else {
            shared_ptr<Team> root = m_parent->getRoot();
            m_parent = root;
            return root;
        }
    } else {
        return nullptr;
    }
}

Node<Team>* Team::getRecordNode() const {
    return m_recordNode;
}