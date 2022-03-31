#ifndef JBlock_h
#define JBlock_h
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "Block.h"

class JBlock : public Block{
    std::string BlockType = "J";
    int currentRotation;
protected:
    std::vector<std::vector <std::string>> v;
public:
    void clockw() override;
    void cclockw() override;
    JBlock();
    ~JBlock();
    void print () override;
    std::vector<std::vector <std::string>> getBlock() override;
    JBlock* clone () override;
    std::unique_ptr<std::JBlock> Aclone() {
        return std::unique_ptr<JBlock> (this->clone());
    }
    std::string GetType () override;
};

#endif