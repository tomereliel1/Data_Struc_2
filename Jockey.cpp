#include "Jockey.h"

Jockey::Jockey(int id, int teamId):m_id(id), m_teamId(teamId) , m_record(0){}

void Jockey::updateVictory() {
    m_record++;
}

void Jockey::updateLoss() {
    m_record--;
}

int Jockey::getRecord() const {
    return m_record;
}

int Jockey::getTeamId() const {
    return m_teamId;
}
