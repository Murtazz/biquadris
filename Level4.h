#ifndef __LEVEL4_H__
#define __LEVEL4_H__

#include "Level.h"


struct Player;

class Level4 : public Level{
    std::vector<std::string> seqList1;
    std::vector<std::string> seqList2;
    int seqCount1;
    int seqCount2;
    bool random1;
    bool random2;
    std::vector<int> seqList1_int;
    std::vector<int> seqList2_int;
    int seqCount1_int;
    int seqCount2_int;
    
public:
    Level4();
    std::shared_ptr<Block> GetBlock(std::shared_ptr<Player> ) override;
    ~Level4();
    void addBlockSeq(std::string,int) override;
    void randomBack(int) override;
    
};


#endif 