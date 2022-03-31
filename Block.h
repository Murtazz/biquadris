#ifndef Block_h
#define Block_h
#include <string>
#include <vector>
#include <memory>
using namespace std;


class Block {
protected:
    vector<vector <string>> v;
public:
    Block ();
    virtual void clockw () = 0;
    virtual void cclockw () = 0;
    virtual ~Block();
    virtual void print () = 0;
    virtual vector<vector <string>> getBlock() = 0;
    virtual Block* clone () = 0;
    std::shared_ptr<Block> Aclone(){
        return std::shared_ptr<Block> (this->clone());
    }
    virtual string GetType () = 0;
    Block (const Block& b);
    Block& operator = (const Block& b);
};

#endif
