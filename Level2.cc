#include "Level2.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>


Level2::Level2(){
    level_num = 2;
    int seqCount1_int = 0;
    int seqCount2_int = 0;
    srand(seedNum);
    for(int i = 0 ; i < 4 ; i++ ) {
        seqList1_int.emplace_back(rand() % 7 + 1);
    }//for player1
    for(int i = 0 ; i < 4 ; i++ ) {
        seqList2_int.emplace_back(rand() % 7 + 1);
    }//for player2
}

//we pretend we need this function but actually not
void Level2::addBlockSeq(std::string filename,int id){}

Level2::~Level2(){};

shared_ptr<Block> Level2::GetBlock(std::shared_ptr<Player> p){
    shared_ptr<Block> b = nullptr;
    int rdmb = 1;
    //
    if(p->id == 1){
        if(seqCount1_int > seqList1_int.size() - 1){//reset
            seqCount1_int = 0;
        }
        rdmb = seqList1_int[seqCount1_int];
        ++seqCount1_int;
        
    } else {
        if(seqCount2_int > seqList2_int.size() - 1){//reset
            seqCount2_int = 0;
        }
        rdmb = seqList2_int[seqCount2_int];
        ++seqCount2_int;
    }
    //
    if (seedFree){
        random_device rd;
        mt19937 eng(rd());
        uniform_int_distribution<> distr(1,7);
        rdmb = distr(eng);
    }
    switch (rdmb){
        case 1: b = make_shared<LBlock>(); break;
        case 2: b = make_shared<IBlock>(); break;
        case 3: b = make_shared<OBlock>(); break;
        case 4: b = make_shared<JBlock>(); break;
        case 5: b = make_shared<TBlock>(); break;
        case 6: b = make_shared<ZBlock>(); break;
        case 7: b = make_shared<SBlock>(); break;
    }
    return b;
}

void Level2::randomBack(int id ){}