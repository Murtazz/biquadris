#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include "Board.h"
#include "Block.h"
#include "cell.h"
#include "Level.h"

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
    // ignore for now
    //Level *levptr;
    std::unique_ptr<Level> levptr;
    bool cwPossible;
    bool ccwPossible;
    std::shared_ptr<Block> CurBlock;
    std::shared_ptr<Block> NextBlock;
    
    bool IsAlive;
    int SpeAttack;
    //int EdgeFlag;

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
    bool reverse;
    
    //for level4
    int notclear = 0;
    bool staron = false;
    int High = 0;
};

#endif