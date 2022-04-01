#ifndef __LEVEL0_H__
#define __LEVEL0_H__

#include "Level.h"


struct Player;
extern std::string seqName1;
extern std::string seqName2;
extern int seedNum;
extern bool seedFree;

class Level0 : public Level{
    
    std::vector<std::string> seqList1;
    std::vector<std::string> seqList2;
    int seqCount1;
    int seqCount2;
    
public:
    Level0();
    std::shared_ptr<Block> GetBlock(std::shared_ptr<Player>  ) override;
    ~Level0();
    void addBlockSeq(std::string,int) override;
    void randomBack(int) override;
};



#endif 