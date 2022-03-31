#include "SBlock.h"
using namespace std;


SBlock::SBlock() {
    currentRotation = 0;
    v.resize(5);
    for (int i = 0; i < 4; ++i){
        v.resize(4);
    }
    v = {
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {" ", "S", "S", " "},
        {"S", "S", " ", " "},
    };
}

SBlock::~SBlock() {}

void SBlock::clockw() {
    if (currentRotation == 0) {
        v = {
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {"S", " ", " ", " "},
            {"S", "S", " ", " "},
            {" ", "S", " ", " "},
        };
        currentRotation = 1;
    }
    else {
        v = {
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {" ", "S", "S", " "},
            {"S", "S", " ", " "},
        };
        currentRotation = 0;
    }
}

void SBlock::cclockw() {
    clockw();
    clockw();
    clockw();
}

void SBlock::print() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << v[i][j];
        }
        cout << endl;
    }
}

vector<vector <string>> SBlock::getBlock() {
    return this->v;
}

SBlock* SBlock::clone() {
    return new SBlock (*this);
}

string SBlock::GetType() {
    return BlockType;
}