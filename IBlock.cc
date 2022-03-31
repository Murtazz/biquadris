#include "IBlock.h"
#include <iostream>

using namespace std;

IBlock:: IBlock(){
    rs = 0;
    v.resize(5);
    for (int i = 0; i < 4; ++i){
        v.resize(4);
    }
    v = {
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {"I", "I", "I", "I"},
        {" ", " ", " ", " "},
    }; 

}

IBlock::~IBlock(){}

void IBlock::clockw(){
    if (rs == 1){
        v = {
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {"I", "I", "I", "I"},
            {" ", " ", " ", " "},
        };
        rs = 0;
    }
    else {
        v = {
            {"I", " ", " ", " "},
            {"I", " ", " ", " "},
            {"I", " ", " ", " "},
            {"I", " ", " ", " "},
            {" ", " ", " ", " "},
        };
        rs = 1;
    }
};

void  IBlock::cclockw(){
   if ( rs == 1){
        v = {
            {"I", " ", " ", " "},
            {"I", " ", " ", " "},
            {"I", " ", " ", " "},
            {"I", " ", " ", " "},
            {" ", " ", " ", " "},
        };
        rs = 0;
    }
    else {
        v = {
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {"I", "I", "I", "I"},
            {" ", " ", " ", " "},
        };
        rs = 1;
    } 
}

void IBlock::print(){
    for (int i = 0; i < 5; ++i){
        for (int j = 0; j < 4; ++j){
            cout << v[i][j];
        }
        cout << endl;
    }
}


vector<vector <string>> IBlock::getBlock(){
    return this->v;
}

IBlock* IBlock::clone (){
    return new IBlock (*this);
}

string IBlock::GetType (){
    return BlockType;
}