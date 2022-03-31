#ifndef __IBLOCK_H__
#define __IBLOCK_H__
#include <string>
#include "Block.h"
#include <memory>
#include <iostream>
#include <vector>
class IBlock : public Block{
    std::string BlockType = "I";
    int currentRotation;
protected:
    std::vector<std::vector <std::string>> v;
public:
    void clockw() override;
    void cclockw() override;
    IBlock();
    ~IBlock();
    void print () override;
    std::vector<std::vector <std::string>> getBlock() override;
    IBlock* clone () override;
    std::unique_ptr<IBlock> Aclone() {
        return std::unique_ptr<IBlock> (this->clone());
    }
    std::string GetType () override;
};

#endif