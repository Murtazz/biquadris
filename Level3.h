#ifndef __LEVEL3_H__
#define __LEVEL3_H__

#include "Level.h"


struct Player;
extern std::string seqName1;
extern std::string seqName2;
extern int seedNum;
extern bool seedFree;

class Level3 : public Level{
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
    
    Level3();
    std::shared_ptr<Block> GetBlock(std::shared_ptr<Player>  ) override;
    ~Level3();
    void addBlockSeq(std::string,int) override;
    void randomBack(int) override;
};

#endif 