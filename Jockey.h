class Jockey {
    int m_id;
    int m_teamId;
    int m_record;
    Jockey* m_nextJockey;
public:
    Jockey(int id, int teamId/*Team* team*/);

    ~Jockey();

    void updateVictory();

    void updateLoss();

    int getRecord() const;

    int getTeamId() const;

    void setNextJockey(Jockey* jockey);

    Jockey* getJockey() const;

};