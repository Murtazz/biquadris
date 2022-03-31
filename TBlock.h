#ifndef TBlock_h
#define TBlock_h

#include "TBlock.h"
#include "Block.h"
#include <string>
#include <iostream>
#include <vector>
class TBlock : public Block{
    std::string BlockType = "T";
    int currentRotation;
protected:
    std::vector<std::vector <std::string>> v;
public:
    void clockw() override;
    void cclockw() override;
    TBlock();
    ~TBlock();
    void print () override;
    std::vector<std::vector <std::string>> getBlock() override;
    TBlock* clone () override;
    std::unique_ptr<TBlock> Aclone() {
        return std::unique_ptr<TBlock> (this->clone());
    }
    std::string GetType () override;
};


#endif