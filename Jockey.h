class Jockey {
    int m_id;
    int m_teamId;
    //Team * m_team;
    int m_record;
    Jockey* m_nextJockey;
public :
    Jockey(int id, int teamId/*Team* team*/);

    void updateVictory();

    void updateLoss();

    int getRecord() const;

    void setNextJockey(Jockey* jockey);

    Jockey* getJockey() const;

};