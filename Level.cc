#include "Level.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>


using namespace std;

extern string seqName1;
extern string seqName2;
extern int seedNum;//for seed, our initial number
extern bool seedFree;



Level::~Level(){}


//Return the int number for which level the player is
int Level:: GetLevel() const{
    return level_num;
}

///////////////////////////Leve0//////////////////////////////


//By creating a level0 class, we need correct sequence1.txt and
//sequence2.txt file
Level0::Level0(){
    
    ifstream seq1{seqName1};
    ifstream seq2{seqName2};
    
    string s;
    while(seq1 >> s){
        string tb1 = s;
        seqList1.emplace_back(tb1);
    }
    while(seq2 >> s){
        string tb2 = s;
        seqList2.emplace_back(tb2);
    }
    
    seqCount1 = 0;
    seqCount2 = 0;
    level_num = 0;
    //
}

Level0::~Level0(){}

//we pretend we need this function but actually not
void Level0::addBlockSeq(std::string filename,int id){}

//Return a block pointer
shared_ptr<Block> Level0::GetBlock(std::shared_ptr<Player> p){
    shared_ptr<Block> b = nullptr;
    char s;
    if(p->id == 1){
        if(seqCount1 > seqList1.size() - 1){//reset
            seqCount1 = 0;
        }
        
        //    cout << "This one is!" << seqList1[seqCount1] << endl;
        s = seqList1[seqCount1][0];
        ++seqCount1;
        
    } else {
        if(seqCount2 > seqList2.size() - 1){//reset
            seqCount2 = 0;
        }
        s = seqList2[seqCount2][0];
        ++seqCount2;
    }
    switch(s){
        case 'J' : b = make_shared<JBlock>();break;
        case 'O' : b = make_shared<OBlock>();break;
        case 'L' : b = make_shared<LBlock>();break;
        case 'I' : b = make_shared<IBlock>();break;
        case 'S' : b = make_shared<SBlock>();break;
        case 'Z' : b = make_shared<ZBlock>();break;
        case 'T' : b = make_shared<TBlock>();break;
            
    }
    return b;
}


void Level0::randomBack(int id ){}