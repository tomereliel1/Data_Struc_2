#include <memory>
using std::shared_ptr;
using std::make_shared;


class Team {
private:
    int m_id;
    int m_teamsNum;
    int m_record;
    shared_ptr<Team> m_parent;

public:
    Team(int id);

    void setParent(shared_ptr<Team> team);

    void addTeamsNum(int teamsNum);

    void addRecord(int record);

    void setId(int id);

    void updateVictory();

    void updateLoss();

    int getRecord() const;

    int getTeamsNum() const;

    int getId() const;

    shared_ptr<Team> getParent() const;

    shared_ptr<Team> getRoot();
};