#ifndef __LEVEL_H
#define __LEVEL_H

#include <stdio.h>
#include <vector>
#include "Block.h"
#include "LBlock.h"
#include "OBlock.h"
#include "JBlock.h"
#include "IBlock.h"
#include "SBlock.h"
#include "ZBlock.h"
#include "TBlock.h"
//#include "XBlock.h"
//#include "CBlock.h"
#include <memory>

struct Player;


//The abstract level class
class Level{
    
public:
    int level_num;
    int GetLevel() const;
    virtual std::shared_ptr<Block> GetBlock(std::shared_ptr<Player> ) = 0;
    virtual ~Level() = 0;
    virtual void addBlockSeq(std::string,int) = 0;
    virtual void randomBack(int) = 0;
    
};



//*************************subclasses****************************


/////////////////////////////Level0///////////////////////////////


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




#endif /* Level_hpp */