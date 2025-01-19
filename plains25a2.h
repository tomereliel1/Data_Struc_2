// 
// 234218 Data Structures 1.
// Semester: 2025A (Winter).
// Wet Exercise #1.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef PLAINS25WINTER_WET1_H_
#define PLAINS25WINTER_WET1_H_
#include "Jockey.h"
#include "Team.h"
#include "Node.h"
#include "HashTable.h"
#include "ChainByRecord.h"
#include "wet2util.h"
#include <iostream>
using namespace std;

class Plains {
private:
    HashTable<Jockey> jockeysTable;
    HashTable<Team> teamsIdTable;
    HashTable<ChainByRecord> teamsRecordTable;
    //int m_jockeyNum;
    //int m_jockeyTableSize;
    // Here you may add anything you want
    //
    void swapTeams (Node<Team>* team1Node, Node<Team>* team2Node){
        shared_ptr<Team >team1 = team1Node->getData();
        shared_ptr<Team >team2 = team2Node->getData();
        int teamId1 = team1->getId();
        int teamId2 = team2->getId();
        team1Node->setData(team2);
        team1Node->setId(teamId2);
        team2Node->setData(team1);
        team2Node->setId(teamId1);
        team1->setId(teamId2);
        team2->setId(teamId1);
    }
public:
    // <DO-NOT-MODIFY> {
    Plains();

    ~Plains();

    StatusType add_team(int teamId);

    StatusType add_jockey(int jockeyId, int teamId);

    StatusType update_match(int victoriousJockeyId, int losingJockeyId);

    StatusType merge_teams(int teamId1, int teamId2);

    StatusType unite_by_record(int record);

    output_t<int> get_jockey_record(int jockeyId);

    output_t<int> get_team_record(int teamId);
    // } </DO-NOT-MODIFY>
};

#endif // PLAINS25WINTER_WET1_H_
