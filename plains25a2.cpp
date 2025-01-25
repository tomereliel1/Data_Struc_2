// You can edit anything you want in this file.
// However you need to implement all public Plains function, as provided below as a template

#include "plains25a2.h"


Plains::Plains() = default;

Plains::~Plains() = default;

StatusType Plains::add_team(int teamId) {
    try {
        if (teamId <= 0) {
            return StatusType::INVALID_INPUT;
        }
        else if (teamsIdTable.find(teamId) != nullptr) {
            return StatusType::FAILURE;
        }
        shared_ptr<Team> newTeam = make_shared<Team>(teamId);
        Node<Team> *teamIdNode = new Node<Team>(teamId, newTeam);
        teamsIdTable.insert(teamIdNode);
        Node<Team> *teamRecordNode = new Node<Team>(teamId, newTeam);
        newTeam->setRecordNode(teamRecordNode);
        Node<ChainByRecord> *chainRecordNode = teamsRecordTable.find(0);
        if (chainRecordNode != nullptr) {
            chainRecordNode->getData()->add(teamRecordNode);
        }
        else {
            shared_ptr<ChainByRecord> record = make_shared<ChainByRecord>(0);
            Node<ChainByRecord> *recordNode = new Node<ChainByRecord>(0, record);
            teamsRecordTable.insert(recordNode);
            teamsRecordTable.find(0)->getData()->add(teamRecordNode);
        }
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;

}

StatusType Plains::add_jockey(int jockeyId, int teamId) {
    try {
        if (jockeyId <= 0 || teamId <= 0) {
            return StatusType::INVALID_INPUT;
        }
        else if (jockeysTable.find(jockeyId) != nullptr) {
            return StatusType::FAILURE;
        }
        else {
            Node<Team> *team = teamsIdTable.find(teamId);
            if (team == nullptr) {
                return StatusType::FAILURE;
            }
            else if (team->getData()->getParent() != nullptr) {
                return StatusType::FAILURE;
            }
        }
        shared_ptr<Jockey> newJockey = make_shared<Jockey>(jockeyId, teamId);
        Node<Jockey> *jockeyNode = new Node<Jockey>(jockeyId, newJockey);
        jockeysTable.insert(jockeyNode);
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::update_match(int victoriousJockeyId, int losingJockeyId) {
    try {
        if (victoriousJockeyId <= 0 || losingJockeyId <= 0 ||
            victoriousJockeyId == losingJockeyId) {
            return StatusType::INVALID_INPUT;
        }
        else if (jockeysTable.find(victoriousJockeyId) == nullptr ||
                 jockeysTable.find(losingJockeyId) == nullptr) {
            return StatusType::FAILURE;
        }

        shared_ptr<Jockey> winner = jockeysTable.find(victoriousJockeyId)->getData();
        int teamId1 = winner->getTeamId();
        shared_ptr<Jockey> loser = jockeysTable.find(losingJockeyId)->getData();
        int teamId2 = loser->getTeamId();
        if (teamId1 == teamId2) {
            return StatusType::FAILURE;
        }

        shared_ptr<Team> winTeam = getRootTeam(teamId1);
        shared_ptr<Team> loseTeam = getRootTeam(teamId2);

        if (winTeam == loseTeam) {
            return StatusType::FAILURE;
        }
        winner->updateVictory();
        loser->updateLoss();

        int oldRecord = winTeam->getRecord();
        Node<ChainByRecord> *oldRecordNode = teamsRecordTable.find(oldRecord);
        Node<Team> *winTeamNode = oldRecordNode->getData()->remove(winTeam);
        if (oldRecordNode->getData()->getSize() == 0) {
            teamsRecordTable.remove(oldRecord);
        }
        winTeam->updateVictory();
        int newRecord = winTeam->getRecord();
        Node<ChainByRecord> *newRecordNode = teamsRecordTable.find(newRecord);
        if (newRecordNode == nullptr) {
            shared_ptr<ChainByRecord> record = make_shared<ChainByRecord>(newRecord);
            Node<ChainByRecord> *recordNode = new Node<ChainByRecord>(newRecord, record);
            teamsRecordTable.insert(recordNode);
            record->add(winTeamNode);
        }
        else {
            newRecordNode->getData()->add(winTeamNode);
        }


        oldRecord = loseTeam->getRecord();
        oldRecordNode = teamsRecordTable.find(oldRecord);
        Node<Team> *loseTeamNode = oldRecordNode->getData()->remove(loseTeam);
        if (oldRecordNode->getData()->getSize() == 0) {
            teamsRecordTable.remove(oldRecord);
        }
        loseTeam->updateLoss();
        newRecord = loseTeam->getRecord();
        newRecordNode = teamsRecordTable.find(newRecord);
        if (newRecordNode == nullptr) {
            shared_ptr<ChainByRecord> record = make_shared<ChainByRecord>(newRecord);
            Node<ChainByRecord> *recordNode = new Node<ChainByRecord>(newRecord, record);
            teamsRecordTable.insert(recordNode);
            teamsRecordTable.find(newRecord)->getData()->add(loseTeamNode);
        }
        else {
            newRecordNode->getData()->add(loseTeamNode);
        }
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}


StatusType Plains::merge_teams(int teamId1, int teamId2) {
    try {
        if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
            return StatusType::INVALID_INPUT;
        }
        Node<Team> *team1IdNode = teamsIdTable.find(teamId1);
        Node<Team> *team2IdNode = teamsIdTable.find(teamId2);
        if (team1IdNode == nullptr || team2IdNode == nullptr) {
            return StatusType::FAILURE;
        }
        shared_ptr<Team> team1 = team1IdNode->getData();
        shared_ptr<Team> team2 = team2IdNode->getData();
        if (team1->getParent() != nullptr || team2->getParent() != nullptr) {
            return StatusType::FAILURE;
        }
        int team1TeamsNum = team1->getTeamsNum();
        int team2TeamsNum = team2->getTeamsNum();
        int team1Record = team1->getRecord();
        int team2Record = team2->getRecord();

        Node<ChainByRecord> *recordNode = teamsRecordTable.find(team1Record);
        shared_ptr<ChainByRecord> recordChain = recordNode->getData();
        Node<Team> *team1RecordNode = recordChain->remove(team1);
        if (recordChain->getSize() == 0) {
            teamsRecordTable.remove(team1Record);
        }
        recordNode = teamsRecordTable.find(team2Record);
        recordChain = recordNode->getData();
        Node<Team> *team2RecordNode = recordChain->remove(team2);
        if (recordChain->getSize() == 0) {
            teamsRecordTable.remove(team2Record);
        }
        Node<Team> *insertTeam = nullptr;
        if (team1Record >= team2Record) {
            if (team1TeamsNum >= team2TeamsNum) {

                team2->setParent(team1);
                team1->addTeamsNum(team2TeamsNum);
                team1->addRecord(team2Record);
                delete team2RecordNode;
                insertTeam = team1RecordNode;
            }
            else {
                swapTeams(team1IdNode, team2IdNode);
                team1->setParent(team2);
                team2->addTeamsNum(team1TeamsNum);
                team2->addRecord(team1Record);
                delete team1RecordNode;
                team2RecordNode->setId(teamId1);
                team2->setRecordNode(team2RecordNode);
                insertTeam = team2RecordNode;
            }
        }
        else {
            if (team1TeamsNum <= team2TeamsNum) {
                team1->setParent(team2);
                team2->addTeamsNum(team1TeamsNum);
                team2->addRecord(team1Record);
                delete team1RecordNode;
                insertTeam = team2RecordNode;
            }
            else {
                swapTeams(team1IdNode, team2IdNode);
                team2->setParent(team1);
                team1->addTeamsNum(team2TeamsNum);
                team1->addRecord(team2Record);
                delete team2RecordNode;
                team1RecordNode->setId(teamId2);
                team1->setRecordNode(team1RecordNode);
                insertTeam = team1RecordNode;

            }
        }
        int newRecord = insertTeam->getData()->getRecord();
        Node<ChainByRecord> *newRecordNode = teamsRecordTable.find(newRecord);
        if (newRecordNode == nullptr) {
            shared_ptr<ChainByRecord> record = make_shared<ChainByRecord>(newRecord);
            Node<ChainByRecord> *recordNode = new Node<ChainByRecord>(newRecord, record);
            teamsRecordTable.insert(recordNode);
            record->add(insertTeam);
        }
        else {
            newRecordNode->getData()->add(insertTeam);
        }
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Plains::unite_by_record(int record) {
    try {
        if (record <= 0) {
            return StatusType::INVALID_INPUT;
        }
        Node<ChainByRecord> *positiveRecord = teamsRecordTable.find(record);
        Node<ChainByRecord> *negativeRecord = teamsRecordTable.find(-record);
        if (positiveRecord == nullptr || negativeRecord == nullptr) {
            return StatusType::FAILURE;
        }
        else if (positiveRecord->getData()->getSize() != 1 ||
                 negativeRecord->getData()->getSize() != 1) {
            return StatusType::FAILURE;
        }
        Node<Team> *team1Node = positiveRecord->getData()->getChain();
        Node<Team> *team2Node = negativeRecord->getData()->getChain();
        int team1Id = team1Node->getId();
        int team2Id = team2Node->getId();
        merge_teams(team1Id, team2Id);
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

output_t<int> Plains::get_jockey_record(int jockeyId) {
    try {
        if (jockeyId <= 0) {
            return {StatusType::INVALID_INPUT};
        }
        Node<Jockey> *jockeyNode = jockeysTable.find(jockeyId);
        if (jockeyNode == nullptr) {
            return {StatusType::FAILURE};
        }
        return {jockeyNode->getData()->getRecord()};
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

output_t<int> Plains::get_team_record(int teamId) {
    try {
        if (teamId <= 0) {
            return {StatusType::INVALID_INPUT};
        }
        Node<Team> *teamNode = teamsIdTable.find(teamId);
        if (teamNode == nullptr) {
            return {StatusType::FAILURE};
        }
        shared_ptr<Team> team = teamNode->getData();
        if (team->getParent() != nullptr) {
            return {StatusType::FAILURE};
        }
        return team->getRecord();
    } catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

void Plains::swapTeams(Node<Team> *team1Node, Node<Team> *team2Node) {
    shared_ptr<Team> team1 = team1Node->getData();
    shared_ptr<Team> team2 = team2Node->getData();
    int teamId1 = team1->getId();
    int teamId2 = team2->getId();
    team1Node->setData(team2);
    team2Node->setData(team1);
    team1->setId(teamId2);
    team2->setId(teamId1);
}

shared_ptr<Team> Plains::getRootTeam(int teamId) {
    shared_ptr<Team> team = teamsIdTable.find(teamId)->getData();
    shared_ptr<Team> root = team->getRoot();
    if (root == nullptr) {
        return team;
    }
    return root;
}