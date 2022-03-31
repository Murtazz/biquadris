#ifndef __SBLOCK_H__
#define __SBLOCK_H__
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "Block.h"

class SBlock: public Block {
    std::string BlockType = "S";
    int currentRotation;
protected:
    std::vector<std::vector <string>> v;
public:
    void clockw() override;
    void cclockw() override;
    SBlock();
    ~SBlock();
    void print() override;
    std::vector<std::vector <std::string>> getBlock() override;
    SBlock* clone() override;
    std::unique_ptr<SBlock> Aclone() {
        return std::unique_ptr<SBlock> (this->clone());
    }
    string GetType() override;
};

#endif 
