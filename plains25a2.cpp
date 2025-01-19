// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a2.h"


Plains::Plains() = default;
//{
    //jockeysTable = *new HashTable<Jockey>();
    //teamsIdTable = *new HashTable<Team>();
    //teamsRecordTable = *new HashTable<ChainByRecord>();

//}

Plains::~Plains()
{
    
}

StatusType Plains::add_team(int teamId) {
    try {
        if (teamId <= 0) {
            return StatusType::INVALID_INPUT;
        } else if (teamsIdTable.find(teamId) != nullptr) {
            return StatusType::FAILURE;
        }
        shared_ptr<Team> newTeam = make_shared<Team>(teamId);
        Node<Team> *teamNode = new Node<Team>(teamId, newTeam);
        teamsIdTable.insert(teamNode);
        if (teamsRecordTable.find(0) != nullptr){
            teamsRecordTable.find(0)->getData()->add(teamNode);
        } else {
            shared_ptr<ChainByRecord> record = make_shared<ChainByRecord>(0);
            Node<ChainByRecord> *recordNode = new Node<ChainByRecord>(0, record);
            teamsRecordTable.insert(recordNode);
            teamsRecordTable.find(0)->getData()->add(teamNode);
        }
    } catch (std::bad_alloc &e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;

}

StatusType Plains::add_jockey(int jockeyId, int teamId)
{
    try{
        if (jockeyId <=0 || teamId <= 0){
            return StatusType::INVALID_INPUT;
        } else if (jockeysTable.find(jockeyId) != nullptr){
            return StatusType::FAILURE;
        } else {
            Node<Team> *team = teamsIdTable.find(teamId);
            if (team == nullptr) {
                return StatusType::FAILURE;
            }
            else if (team->getData()->getParent() != nullptr) {
                return StatusType::FAILURE;
            }
        }
        shared_ptr<Jockey> newJockey = make_shared<Jockey>(jockeyId, teamId);
        Node<Jockey> *jockeyNode = new Node<Jockey>(teamId, newJockey);
        jockeysTable.insert(jockeyNode);
    } catch (std::bad_alloc &e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::update_match(int victoriousJockeyId, int losingJockeyId)
{
    try {
        if (victoriousJockeyId <= 0 || losingJockeyId <= 0){
            return StatusType::INVALID_INPUT;
        } else if (jockeysTable.find(victoriousJockeyId) == nullptr || jockeysTable.find(losingJockeyId) == nullptr){
            return StatusType::FAILURE;
        }
        shared_ptr<Jockey> winner = jockeysTable.find(victoriousJockeyId)->getData();
        winner->updateVictory();
        shared_ptr<Team> winTeam = teamsIdTable.find(winner->getTeamId())->getData()->getRoot();
        int oldRecord = winTeam->getRecord();
        Node<ChainByRecord>* oldRecordNode = teamsRecordTable.find(oldRecord);
        Node<Team>* winTeamNode = oldRecordNode->getData()->remove(winTeam->getId());
        if (oldRecordNode->getData()->getSize() == 0){
            teamsRecordTable.remove(oldRecord);
        }
        winTeam->updateVictory();
        int newRecord = winTeam->getRecord();
        Node<ChainByRecord>* newRecordNode = teamsRecordTable.find(newRecord);
        if (newRecordNode == nullptr){
            shared_ptr<ChainByRecord> record = make_shared<ChainByRecord>(newRecord);
            Node<ChainByRecord> *recordNode = new Node<ChainByRecord>(newRecord, record);
            teamsRecordTable.insert(recordNode);
            teamsRecordTable.find(newRecord)->getData()->add(winTeamNode);
        } else {
            newRecordNode->getData()->add(winTeamNode);
        }

        shared_ptr<Jockey> loser = jockeysTable.find(losingJockeyId)->getData();
        loser->updateLoss();
        shared_ptr<Team> loseTeam = teamsIdTable.find(loser->getTeamId())->getData()->getRoot();
        oldRecord = loseTeam->getRecord();
        oldRecordNode = teamsRecordTable.find(oldRecord);
        Node<Team>* loseTeamNode = oldRecordNode->getData()->remove(loseTeam->getId());
        if (oldRecordNode->getData()->getSize() == 0){
            teamsRecordTable.remove(oldRecord);
        }
        loseTeam->updateLoss();
        newRecord = loseTeam->getRecord();
        newRecordNode = teamsRecordTable.find(newRecord);
        if (newRecordNode == nullptr){
            shared_ptr<ChainByRecord> record = make_shared<ChainByRecord>(newRecord);
            Node<ChainByRecord> *recordNode = new Node<ChainByRecord>(newRecord, record);
            teamsRecordTable.insert(recordNode);
            teamsRecordTable.find(0)->getData()->add(loseTeamNode);
        } else {
            newRecordNode->getData()->add(loseTeamNode);
        }
    } catch (std::bad_alloc &e){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}



StatusType Plains::merge_teams(int teamId1, int teamId2)
{
    return StatusType::FAILURE;
}

StatusType Plains::unite_by_record(int record)
{
    return StatusType::FAILURE;
}

output_t<int> Plains::get_jockey_record(int jockeyId)
{
    if (jockeyId <= 0){
        return {StatusType::INVALID_INPUT};
    }
    Node<Jockey>* jockeyNode = jockeysTable.find(jockeyId);
    if (jockeyNode == nullptr){
        return {StatusType::FAILURE};
    }
    return {jockeyNode->getData()->getRecord()};
}

output_t<int> Plains::get_team_record(int teamId)
{
    if (teamId <= 0){
        return {StatusType::INVALID_INPUT};
    }
    Node<Team>* teamNode = teamsIdTable.find(teamId);
    if (teamNode == nullptr){
        return {StatusType::FAILURE};
    }
    shared_ptr<Team> team = teamNode->getData();
    if (team->getParent() != nullptr){
        return {StatusType::FAILURE};
    }
    return team->getRecord();
    return 0;
}
