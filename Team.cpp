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

shared_ptr<Team> Team::getGeneralParent() {
    if (m_parent == nullptr){
        return make_shared<Team>(*this);
    }
    shared_ptr<Team> generalParent;
    while (m_parent->getParent() != nullptr) {
        generalParent = m_parent->getParent();
    }
    return generalParent;
}