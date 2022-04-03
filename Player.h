#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include "Board.h"
#include "Block.h"
#include "Cell.h"
#include "Level.h"
#include "Level0.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"


struct Player{
    std::vector <std::vector <Cell>> PlayField;
    std::string name;
    int id;
    int Score;
    int level;
    int col;
    int row;
    bool LeftPossible;
    bool RightPossible;
    bool DownPossible;
    int cant_down;
    std::unique_ptr<Level> levptr;
    bool clockPossible;
    bool counterCPossible;
    std::shared_ptr<Block> CurBlock;
    std::shared_ptr<Block> NextBlock;
    
    bool IsAlive;
    int SpeAttack;

    // for score
    int IBlock;
    int JBlock;
    int LBlock;
    int OBlock;
    int SBlock;
    int TBlock;
    int ZBlock;
    
    // for Heavy
    bool heavy;
    
    //for level4
    int notclear = 0;
    bool staron = false;
    int High = 0;
};

#endif