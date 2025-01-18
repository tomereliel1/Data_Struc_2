#include "Node.h"
#include "Team.h"
class ChainByRecord{
private:
    int m_record;
    int m_size;
    Node<Team>* m_chain;
public:
    ChainByRecord(int record);

    void add(Node<Team>* node);

    Node<Team>* remove(int id);

    Node<Team>* getChain() const;

    int getSize () const;
};