#ifndef __LEVEL1_H__
#define __LEVEL1_H__

#include "Level.h"

struct Player;
extern std::string seqName1;
extern std::string seqName2;
extern int seedNum;
extern bool seedFree;


class Level1 : public Level{
    std::vector<int> seqList1_int;
    std::vector<int> seqList2_int;
    int seqCount1_int;
    int seqCount2_int;
    
public:
    Level1();
    std::shared_ptr<Block> GetBlock(std::shared_ptr<Player>  ) override;
    ~Level1();
    void addBlockSeq(std::string,int) override;
    void randomBack(int) override;
};

#endif 