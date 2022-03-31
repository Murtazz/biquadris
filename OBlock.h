#ifndef OBlock_h
#define OBlock_h
#include "Block.h"
#include <string>
#include <iostream>
#include <vector>


class OBlock : public Block{
    std::string BlockType = "O";
    int currentRotation;
protected:
    std::vector<std::vector <std::string>> v;
public:
    void clockw() override;
    void  cclockw() override;
    OBlock();
    ~OBlock();
    void print () override;
    std::vector<std::vector <std::string>> getBlock() override;
    OBlock* clone () override;
    std::unique_ptr<OBlock> Aclone() {
        return std::unique_ptr<OBlock> (this->clone());
    }
    std::string GetType () override;
};

#endif