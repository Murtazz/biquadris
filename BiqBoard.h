#ifndef __BIQBOARD_H__
#define __BIQBOARD_H__
#include "Board.h"
#include "Player.h"
#include "Cell.h"
#include "Window.h"
#include "Block.h"

#include <iostream>
#include <vector>
#include <string>
#include <memory>
struct Player;

class BiqBoard : public Board {
    std::shared_ptr <Player> player1;
    std::shared_ptr <Player> player2;
public:
    bool IsText = false;
    // finish part
    BiqBoard ();
    ~BiqBoard ();
    
    // ********************** initialization **********************
    void SetPlayer(std::shared_ptr <Player>& player, std::string playername,int id,int level);
    
    // ********************** Get Private Field from board ********************** (it could be delete, no use)
    std::shared_ptr <Player>& GetPlayer1();
    std::shared_ptr <Player>& GetPlayer2();
    
    // ********************** Get Private Field from player **********************
    int GetCurScore(std::shared_ptr <Player>& player);
    
    // ********************** Draw the whole Board **********************
    void DrawBoard(std::shared_ptr <Player>& player1, std::shared_ptr <Player>& player2, Xwindow * board) override;
    bool DrawBlock(std::shared_ptr <Player>& player, int x, int y);
    void DrawNextBlock(std::shared_ptr <Player>& player1, std::shared_ptr <Player>& player2, Xwindow  * board);
    // helper function of DrawBlock
    bool availableCells(std::shared_ptr <Player>& player, int x, int y);
    
    
    // ********************** switch player **********************
    
    //get player function for this turn's player
    bool turn = true;
    // This bool is to id which player is playing
    // true for player1, flase for player2
    std::shared_ptr <Player>& NowPlayer();
    void switchPlayer();
    std::shared_ptr <Player>& OtherPlayer();
    
    // ********************** Left, Right, Down, Drop, CW, CCW**********************
    void left(std::shared_ptr <Player>& player);
    void right(std::shared_ptr <Player>& player);
    void down(std::shared_ptr <Player>& player);
    void drop(std::shared_ptr <Player>& player);
    void clockPossible (std::shared_ptr <Player>& player);
    void counterCPossible (std::shared_ptr <Player>& player);
    // initialize all possible
    void updatePossibilities();
    // update all possible
    void update(std::shared_ptr <Player>& player);
    
    // ********************** clean line **********************
    int ReCalc(std::shared_ptr <Player>& player) override;
    void ClearLine(std::shared_ptr <Player>& player, std::vector<int> &clean_row);
    
    // ********************** Level UP and Down **********************
    void LevelUp(std::shared_ptr <Player>& player);
    void LevelDown(std::shared_ptr <Player>& player);
    
    // ********************** helper function to test **********************
    void SetDeadCell(std::shared_ptr <Player>& player, int row1, int col1, int row2, int col2);
    void KillLiveCell(std::shared_ptr <Player>& player);
    
    // ********************** Heavy **********************
    void LevelHeavy (std::shared_ptr <Player>& player);
    void BlockHeavy (std::shared_ptr <Player>& player);
    
    // ******************Blind*****************
    void Blind (std::shared_ptr <Player>& player);
    
    // ********************** GameOver **********************
    bool GameOver (std::shared_ptr <Player>& player);
    
    // ********************** Restart **********************
    void Restart(std::shared_ptr <Player>& player1, std::shared_ptr <Player>& player2);
    
    
};

#endif

