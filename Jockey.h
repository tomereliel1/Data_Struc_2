#pragma once
class Jockey {
    int m_id;
    int m_teamId;
    int m_record;
public:
    Jockey(int id, int teamId/*Team* team*/);

    void updateVictory();

    void updateLoss();

    int getRecord() const;

    int getTeamId() const;


};