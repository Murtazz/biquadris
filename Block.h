#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <string>
#include <vector>
#include <memory>


class Block {
protected:
    std::vector<std::vector <std::string>> v;
public:
    Block ();
    virtual void clockw () = 0;
    virtual void cclockw () = 0;
    virtual ~Block();
    virtual void print () = 0;
    virtual std::vector<std::vector <std::string>> getBlock() = 0;
    virtual Block* clone () = 0;
    std::shared_ptr<Block> Aclone(){
        return std::shared_ptr<Block> (this->clone());
    }
    virtual std::string GetType () = 0;
    Block (const Block& b);
    Block& operator = (const Block& b);
};

#endif
