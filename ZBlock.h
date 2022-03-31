#ifndef __ZBLOCK_H__
#define __ZBLOCK_H__
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "Block.h"

class ZBlock: public Block{
    std::string BlockType = "Z";
    int currentRotation;
protected:
    std::vector<std::vector <std::string>> v;
public:
    void clockw() override;
    void cclockw() override;
    ZBlock();
    ~ZBlock();
    void print() override;
    std::vector<std::vector <std::string>> getBlock() override;
    ZBlock* clone() override;
    std::unique_ptr<ZBlock> Aclone() {
        return std::unique_ptr<ZBlock> (this->clone());
    }
    std::string GetType () override;
};

#endif