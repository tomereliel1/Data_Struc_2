// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a2.h"


Plains::Plains() = default;
//{
    //jockeysTable = *new HashTable<Jockey>();
    //teamsIdTable = *new HashTable<Team>();
    //teamsRecordTable = *new HashTable<Team>();

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
        // need to add insert to record table
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
        winTeam->updateVictory();
        jockeysTable.find(victoriousJockeyId)->getData()->updateLoss();
        shared_ptr<Jockey> loser = jockeysTable.find(losingJockeyId)->getData();
        loser->updateLoss();
        jockeysTable.find(losingJockeyId)->getData()->updateLoss();
        shared_ptr<Team> loseTeam = teamsIdTable.find(loser->getTeamId())->getData()->getRoot();
        loseTeam->updateLoss();
        //need to add changing in record hash table
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
