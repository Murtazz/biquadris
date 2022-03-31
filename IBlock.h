#ifndef IBlock_h
#define IBlock_h
#include <string>
#include "Block.hpp"
#include <memory>
using namespace std;
#include <vector>
class IBlock : public Block{
    string BlockType = "I";
    int rs;
protected:
    vector<vector <string>> v;
public:
    void clockw() override;
    void cclockw() override;
    IBlock();
    ~IBlock();
    void print () override;
    vector<vector <string>> getBlock() override;
    IBlock* clone () override;
    std::unique_ptr<IBlock> Aclone() {
        return std::unique_ptr<IBlock> (this->clone());
    }
    string GetType () override;
};

#endif