#ifndef __LBLOCK_H__
#define __LBLOCK_H__
#include "Block.h"
#include <string>
#include <vector>
class LBlock : public Block{
    std::string BlockType = "L";
    int currentRotation;
protected:
    std::vector<vector <string>> v;

public:
    void clockw() override;
    void cclockw() override;
    LBlock();
    ~LBlock();
    void print () override;
    std::vector<std::vector <std::string>> getBlock() override;
    LBlock* clone () override;
    std::unique_ptr<LBlock> Aclone() {
        return std::unique_ptr<LBlock> (this->clone());
    }
    std::string GetType () override;
};

#endif