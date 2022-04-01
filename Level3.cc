#include "Level3.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>

Level3::Level3(){
    level_num = 3;
    random1 = true;//yes default is random
    random2 = true;
    seqCount1 = 0;
    seqCount2 = 0;//
    seqCount1_int = 0;
    seqCount2_int = 0;
    
    srand(seedNum);
    for(int i = 0 ; i < 4 ; i++ ) {
        seqList1_int.emplace_back(rand() % 9 + 1);
    }//for player1
    for(int i = 0 ; i < 4 ; i++ ) {
        seqList2_int.emplace_back(rand() % 9 + 1);
    }//for player2
}

Level3::~Level3(){}

void Level3::addBlockSeq(std::string filename,int id){
    string s;
    if (id == 1){
        ifstream seq1{filename};
        while(seq1 >> s){
            string tb1 = s;
            seqList1.emplace_back(tb1);
        }
        random1 = false;
    }else {
        ifstream seq2{filename};
        while(seq2 >> s){
            string tb2 = s;
            seqList2.emplace_back(tb2);
        }
        random2 = false;
    }
}

shared_ptr<Block> Level3::GetBlock(std::shared_ptr<Player> p){
    shared_ptr<Block> b = nullptr;
    bool random = false;
    if ((p->id == 1) && random1) random = true;
    if ((p->id == 2) && random2) random = true;
    if(random){
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
            uniform_int_distribution<> distr(1,9);
            rdmb = distr(eng);
        }
        switch (rdmb){
            case 1: b = make_shared<LBlock>(); break;
            case 2: b = make_shared<IBlock>(); break;
            case 3: b = make_shared<OBlock>(); break;
            case 4: b = make_shared<JBlock>(); break;
            case 5: b = make_shared<TBlock>(); break;
            case 6: b = make_shared<SBlock>(); break;
            case 7: b = make_shared<SBlock>(); break;
            case 8: b = make_shared<ZBlock>(); break;
            case 9: b = make_shared<ZBlock>(); break;
        }
    }else{//random flag is false , we will not be random anymore!!!
        
        //we use that weird file for get block
        char s;
        if(p->id == 1){
            if(seqCount1 > seqList1.size() - 1){//reset
                seqCount1 = 0;
            }
            
            //cout << "This one is!" << seqList1[seqCount1] << endl;
            s = seqList1[seqCount1][0];
            ++seqCount1;
            
        } else {//p->id == 2
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
    }
    return b;
}

void Level3::randomBack(int id ){
    if (id == 1){
        random1 = true;
    }else if (id == 2){
        random2 = true;
    }
    
}