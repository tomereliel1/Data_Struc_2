#include "Team.h"

Team::Team(int id):m_id(id), m_teamsNum(0) , m_record(0), m_parent(nullptr){}

void Team::updateVictory() {
    m_record++;
}

void Team::updateLoss() {
    m_record--;
}

int Team::getRecord() const {
    return m_record;
}

void Team::setParent(shared_ptr<Team> team) {
    m_parent = team;
}

shared_ptr<Team> Team::getParent() const {
    return m_parent;
}

shared_ptr<Team> Team::getRoot() {
    if (m_parent == nullptr){
        return make_shared<Team>(*this);
    }
    shared_ptr<Team> root = m_parent->getRoot();
    m_parent = root;
    return root;
}