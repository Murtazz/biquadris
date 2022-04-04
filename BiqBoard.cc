#include "BiqBoard.h"
#include "Player.h"
#include <iostream>
#include <string>

extern bool specialOn;


using namespace std;

BiqBoard::BiqBoard () {
    pler1 = shared_ptr <Player> (new Player);
    pler2 = shared_ptr <Player> (new Player);
}

BiqBoard::~BiqBoard(){
}


// ********************** initialization **********************
void BiqBoard::SetPler(shared_ptr <Player> &pler, string playername,int id,int level) {
    
    pler->PlayField.resize(15);
    for (int row = 0; row < 15; row++) {
        pler->PlayField[row].resize(11);
        for (int col = 0; col < 11; col++) {
            pler->PlayField[row][col] = Cell();
        }
    }
    //for level
    if (level == 0) {
        pler->levptr = unique_ptr <Level> (new Level0);
    } else if (level == 1) {
        pler->levptr = unique_ptr <Level> (new Level1);
    } else if (level == 2) {
        pler->levptr= unique_ptr <Level> (new Level2);
    } else if (level == 3) {
        pler->levptr= unique_ptr <Level> (new Level3);
    } else if (level == 4) {
        pler->levptr= unique_ptr <Level> (new Level4);
    } 
    
    
    pler->id = id;
    
    pler->CurBlock = nullptr;
    pler->NextBlock = nullptr;
    pler->name = playername;
    pler->Score = 0;
    pler->level = level;
    pler->IsAlive = true;
    pler->SpeAttack = 0;
    pler->col = 0;
    pler->row = 0;
    pler->cant_down = 0;
    pler->LeftPossible = true;
    pler->RightPossible = true;
    pler->DownPossible = true;
    pler->clockPossible = true;
    pler->counterCPossible = true;
    
    pler->IBlock = 0;
    pler->JBlock = 0;
    pler->LBlock = 0;
    pler->OBlock = 0;
    pler->SBlock = 0;
    pler->TBlock = 0;
    pler->ZBlock = 0;
    

    pler->heavy = false;
}

// ********************** Get Private Field from board ********************** (it could be delete, no use)
shared_ptr <Player>& BiqBoard::Getpler1() {
    return pler1;
    
}

shared_ptr <Player>& BiqBoard::Getpler2() {
    return pler2;
}





// ********************** Get Private Field from pler **********************
int BiqBoard::gCS(shared_ptr <Player>& pler) {
    return pler->Score;
}




string NumToString(int num) {
    string s = "";
    if(num == 0) {
        s = "0";
    } else {
        while(num != 0){
            int con = num % 10;
            switch (con){
                case 1: s = s + "1"; break;
                case 2: s = s + "2"; break;
                case 3: s = s + "3"; break;
                case 4: s = s + "4"; break;
                case 5: s = s + "5"; break;
                case 6: s = s + "6"; break;
                case 7: s = s + "7"; break;
                case 8: s = s + "8"; break;
                case 9: s = s + "9"; break;
                case 0: s = s + "0"; break;
            }
            num = num / 10;
        }
    }
    return s;
}

// ********************** Draw the whole Board **********************
// I add a Xwindow pointer here!!!
void BiqBoard::DrawBoard(shared_ptr <Player>& pler1, shared_ptr <Player>& pler2, Xwindow * board) {
    int temp_col = 0;
    cout << "Level:    " << pler1->level << "     " << "Level:    " << pler2->level << endl;
    cout << "Score:    " << pler1->Score << "     " << "Score:    " << pler2->Score << endl;
    cout << "High :    " << pler1->High << "     " << "High :    " << pler2->High << endl;
    if (!IsText){
        board->fillRectangle(0, 0, 600, 30, 5);
        board->drawString(5, 25, "Level:", 7);
        string levelStr1 = NumToString(pler1->level);
        board->drawString(55, 25, levelStr1, 7);
        
        board->drawString(100, 25, "Score:", 7);
        string scoreStr1 = NumToString(pler1->Score);
        board->drawString(150, 25, scoreStr1, 7);
        
        board->drawString(200, 25, "High:", 7);
        string highStr1 = NumToString(pler1->High);
        board->drawString(250, 25, highStr1, 7);
        
        board->drawString(330, 25, "Level:", 7);
        string levelStr2 = NumToString(pler2->level);
        board->drawString(380, 25, levelStr2, 7);
        
        board->drawString(425, 25, "Score:", 7);
        string scoreStr2 = NumToString(pler2->Score);
        board->drawString(475, 25, scoreStr2, 7);
        
        board->drawString(525, 25, "High:", 7);
        string highStr2 = NumToString(pler2->High);
        board->drawString(575, 25, highStr2, 7);
    }
    
    cout << "-----------     -----------" << endl;
    if (!IsText){
        board->drawLine(0, 50, 265, 50);
        board->drawLine(350, 50, 600, 50);
    }
    for (int row = 0; row < 15; row++) {
        
        for (int col1 = 0; col1 < 11; col1++) {
            cout << pler1->PlayField[row][col1];
            if (!IsText){
                pler1->PlayField[row][col1].draw(col1, row+2, board);
                temp_col = col1;
            }
            
        }
        cout << "     ";
        for (int col2 = 0; col2 < 11; col2++) {
            cout << pler2->PlayField[row][col2];
            if (!IsText){
                pler2->PlayField[row][col2].draw(col2+temp_col+3, row+2, board);
            }
        }
        cout << endl;
        
        if ((row+1) == 15){
            cout << "-----------     -----------" << endl;
            cout << "Next:           Next:      " << endl;
            if (!IsText){
                board->drawString(5, 440, "Next:", 7);
                board->drawString(330, 440, "Next:", 7);
            }
        }
        
    }
    if (!IsText) {
        for (int i = 18; i < 30; ++i) {
            for (int j = 0; j < 24; ++j) {
                board->fillRectangle(j*25, i*25, 25, 25, 16);
            }
        }
    }
    DrawNextBlock(pler1, pler2, board);
}




bool BiqBoard::DrawBlock(shared_ptr <Player>& pler, int x, int y) {
    int block_row = 5;
    int block_col = 4;
    int board_row = 15;
    int board_col = 11;
    bool ava = availableCells(pler, x, y);
    vector <vector <string>> v = pler->CurBlock->getBlock();
    
    
    for (int row = 0; row < block_row; ++ row) {
        for (int col = 0; col < block_col; ++ col) {
            int new_row = row + x;
            int new_col = col + y;
            string color = v[row][col];
            if ((new_col >= board_col)||(new_row >= board_row)||(color == " ")) {
                continue;
            }
            else {
                if (pler->cant_down == 1) {
                    pler->PlayField[new_row][new_col].TurnOff(color);
                    continue;
                }
                if (ava){
                    pler->PlayField[new_row][new_col].TurnOn(color);
                }
            }
        }
    }
    // return a bool to tell to change the block
    if (pler->cant_down == 1) {
        pler->cant_down = 0;
        pler->col = 0;
        pler->row = 0;
        pler->CurBlock = pler->NextBlock;
        pler->RightPossible = true;
        pler->LeftPossible = true;
        pler->DownPossible = true;
        pler->clockPossible = true;
        pler->counterCPossible = true;
        return true;
    }
    return false;
}



void BiqBoard::DrawNextBlock(shared_ptr <Player>& pler1, shared_ptr <Player>& pler2, Xwindow * board){
    shared_ptr<Block> p1 = pler1->NextBlock;
    shared_ptr<Block> p2 = pler2->NextBlock;
    vector<vector<string>> b1 = p1->getBlock();
    vector<vector<string>> b2 = p2->getBlock();
    
    for (int i = 2; i < 5; ++i){
        for (int j = 0; j < 4; ++j){
            cout << b1[i][j];
            if (!IsText){
                if (b1[i][j] != " ") {
                    if (b1[i][j] == "I") {
                        board->fillRectangle((3+j)*25, (16+i)*25, 25, 25, 7);
                    } else if (b1[i][j] == "J"){
                        board->fillRectangle((3+j)*25, (16+i)*25, 25, 25, 9);
                    } else if (b1[i][j] == "L"){
                        board->fillRectangle((3+j)*25, (16+i)*25, 25, 25, 0);
                    } else if (b1[i][j] == "Z"){
                        board->fillRectangle((3+j)*25, (16+i)*25, 25, 25, 6);
                    } else if (b1[i][j] == "S"){
                        board->fillRectangle((3+j)*25, (16+i)*25, 25, 25, 3);
                    } else if (b1[i][j] == "O"){
                        board->fillRectangle((3+j)*25, (16+i)*25, 25, 25, 4);
                    } else if (b1[i][j] == "T"){
                        board->fillRectangle((3+j)*25, (16+i)*25, 25, 25, 8);
                    }
                }
            }
        }
        cout << "            ";
        for (int j = 0; j < 4; ++j){
            cout << b2[i][j];
            if (!IsText){
                if (b2[i][j] != " "){
                    if (b2[i][j] == "I") {
                        board->fillRectangle((16+j)*25, (16+i)*25, 25, 25, 7);
                    } else if (b2[i][j] == "J"){
                        board->fillRectangle((16+j)*25, (16+i)*25, 25, 25, 9);
                    } else if (b2[i][j] == "L"){
                        board->fillRectangle((16+j)*25, (16+i)*25, 25, 25, 0);
                    } else if (b2[i][j] == "Z"){
                        board->fillRectangle((16+j)*25, (16+i)*25, 25, 25, 6);
                    } else if (b2[i][j] == "S"){
                        board->fillRectangle((16+j)*25, (16+i)*25, 25, 25, 3);
                    } else if (b2[i][j] == "O"){
                        board->fillRectangle((16+j)*25, (16+i)*25, 25, 25, 4);
                    } else if (b2[i][j] == "T"){
                        board->fillRectangle((16+j)*25, (16+i)*25, 25, 25, 8);
                    }
                }
            }
        }
        cout << endl;
    }
}



// helper function of DrawBlock
bool BiqBoard::availableCells(shared_ptr <Player>& pler, int x, int y) {
    int block_row = 5;
    int block_col = 4;
    int board_row = 15;
    int board_col = 11;
    vector <vector <string>> v = pler->CurBlock->getBlock();
    for (int row = 0; row < block_row; ++ row) {
        for (int col = 0; col < block_col; ++ col) {
            int new_row = row + x;
            int new_col = col + y;
            string color = v[row][col];
            if ((new_col >= board_col)||(new_row >= board_row)||(color == " ")) {
                continue;
            }
            else if (pler->PlayField[new_row][new_col].GetColor() != " "){
                return false;
                break;
            }
        }
    }
    return true;
}





// ********************** switch pler **********************

shared_ptr <Player>& BiqBoard::NowPlayer() {
    if (turn){
        return pler1;
    }else{
        return pler2;
    }
}

shared_ptr <Player>& BiqBoard::OtherPlayer() {
    if (turn){
        return pler2;
    }else{
        return pler1;
    }
}



void BiqBoard::switchPlayer() {
    turn = !turn;
}





// ********************** Left, Right, Down, Drop, CW, CCW**********************
void BiqBoard::left(shared_ptr <Player>& pler){
    int player_col = pler->col;
    if ((player_col > 0)&&(pler->LeftPossible)){
        
        pler->col -= 1;
        pler->RightPossible = true;
        pler->DownPossible = true;
    }
    else {
        pler->RightPossible = true;
        pler->LeftPossible = true;
        pler->DownPossible = true;
    }
    pler->clockPossible = true;
    pler->counterCPossible = true;
}



void BiqBoard::right(shared_ptr <Player>& pler){
    int player_col = pler->col;
    int require_col = 0;
    int board_col = 11;
    for (int row = 0; row < 5; ++ row) {
        for (int col = 0; col < 4; ++col) {
            vector <vector <string>> v = pler->CurBlock->getBlock();
            if ((v[row][col] != " ")&&(col > require_col)) {
                require_col = col;
            }
        }
    }
    
    
    if ((player_col + require_col + 2 <= board_col) && (pler->RightPossible)) {
        
        pler->col += 1;
        pler->LeftPossible = true;
        pler->DownPossible = true;
        
    }
    else if (!pler->RightPossible) {
        pler->RightPossible = true;
        pler->LeftPossible = true;
        pler->DownPossible = true;
    }
    pler->clockPossible = true;
    pler->counterCPossible = true;
}



void BiqBoard::down(shared_ptr <Player>& pler){
    int player_row = pler->row;
    if (!pler->DownPossible) {
        ++pler->notclear;//
        //  cout << "can't down" << endl;
        pler->cant_down += 1;
        for (int i = 0; i < 15; ++i){
            for (int j = 0; j < 11; ++j){
                pler->PlayField[i][j].NotBlind();
            }
        }
    }
    
    if ((player_row < 15)&&(pler->DownPossible)){
        pler->row += 1;
        pler->RightPossible = true;
        pler->LeftPossible = true;
    } else {
        pler->RightPossible = true;
        pler->LeftPossible = true;
        pler->DownPossible = true;
    }
    pler->clockPossible = true;
    pler->counterCPossible = true;
    
};



void BiqBoard::drop(shared_ptr <Player>& pler) {
    while (pler->cant_down == 0) {
        update(pler);
        down(pler);
        update(pler);
    }
}



void BiqBoard::clockPossible(shared_ptr <Player>& pler){
    int x = pler->row;
    int y = pler->col;
    int block_row = 5;
    int block_col = 4;
    int board_row = 15;
    int board_col = 11;
    shared_ptr<Block>copy = pler->CurBlock->blockCpy();
    copy->clockw();
    string BlkType = copy->Type();
    
    for (int row = 0; row < block_row; ++ row) {
        for (int col = 0; col < block_col; ++ col) {
            
            int new_row = row + x;
            int new_col = col + y;
            if ((new_col >= 11) && (BlkType == "I")){
                pler->clockPossible = false;
                break;
            }
            if ((new_col > 11) && (BlkType != "I")){
                pler->clockPossible = false;
                break;
            }
            
            //heap copy the block and cw rotate it *************
            vector <vector <string>> v_copy = copy->getBlock();
            string cwcolor = v_copy[row][col];
            //
            
            //ignore white space
            if ((new_col >= board_col)||(new_row >= board_row)||(cwcolor == " ")) {
                continue;
            }
            //cw checkingcw
            
            if (pler->PlayField[new_row][new_col].GetColor() != " "){
                pler->clockPossible = false;
                break;
            }
        }
    }
}



void BiqBoard::counterCPossible(shared_ptr <Player>& pler){
    int x = pler->row;
    int y = pler->col;
    int block_row = 5;
    int block_col = 4;
    int board_row = 15;
    int board_col = 11;
    shared_ptr<Block>copy = pler->CurBlock->blockCpy();
    copy->cclockw();
    string BlkType = copy->Type();
    
    for (int row = 0; row < block_row; ++ row) {
        for (int col = 0; col < block_col; ++ col) {
            
            int new_row = row + x;
            int new_col = col + y;
            if ((new_col >= 11) && (BlkType == "I")){
                pler->counterCPossible = false;
                break;
            }
            if ((new_col > 11) && (BlkType != "I")){
                pler->counterCPossible = false;
                break;
            }
            
            //heap copy the block and cw rotate it *************
            vector <vector <string>> v_copy = copy->getBlock();
            string cwcolor = v_copy[row][col];
            //
            
            //ignore white space
            if ((new_col >= board_col)||(new_row >= board_row)||(cwcolor == " ")) {
                continue;
            }
            //cw checkingcw
            
            
            
            if (pler->PlayField[new_row][new_col].GetColor() != " "){
                pler->counterCPossible = false;
                break;
            }
        }
    }
}



// initialize all possible
void BiqBoard::updatePossibilities () {
    pler1->DownPossible = true;
    pler1->RightPossible = true;
    pler1->LeftPossible = true;
    pler2->DownPossible = true;
    pler2->RightPossible = true;
    pler2->LeftPossible = true;
}



// update all possible
void BiqBoard::update(shared_ptr <Player>& pler){
    int x = pler->row;
    int y = pler->col;
    int block_row = 5;
    int block_col = 4;
    int board_row = 15;
    int board_col = 11;
    int check_row = 0;
    vector <vector <string>> v = pler->CurBlock->getBlock();
    
    for (int row = 0; row < block_row; ++ row) {
        check_row = 0;    // reset check_row
        for (int col = 0; col < block_col; ++ col) {
            int new_row = row + x;
            int new_col = col + y;
            string color = v[row][col];
            if ((new_col >= board_col)||(new_row >= board_row)||(color == " ")) {
                continue;
            }
            else {
                if ((new_col+1 > 10)||(pler->PlayField[new_row][new_col+1].GetColor() != " ")){
                    pler->RightPossible = false;
                }
                //cout << "it pass right possible" << endl;
                if (check_row == 0) {
                    check_row += 1;
                    if ((new_col -1 < 0)|| (pler->PlayField[new_row][new_col-1].GetColor() != " ")){
                        pler->LeftPossible = false;
                    }
                }
                //cout << "it pass left possible" << endl;
                
                if ((new_row+1 >= 15) || (pler->PlayField[new_row+1][new_col].GetColor() != " ")){
                    pler->DownPossible = false;
                }
                //cout << "it pass down possible" << endl;
                
                
                
                
            }
        }
    }
    clockPossible(pler);
    counterCPossible(pler);
}

// ********************** clean line **********************
int BiqBoard::ReCalc(shared_ptr <Player>& pler) {
    vector < int > clean_row;
    for (int row = 14; row > 0 ; row-- ) {
        int num_dead_cell = 0;
        for (int col = 0; col < 11; ++col) {
            if (pler->PlayField[row][col].GetColor() == " ") {
                continue;
            }
            else if ((!pler->PlayField[row][col].IsAlive())&&(pler->PlayField[row][col].GetColor() != " ")) {
                num_dead_cell += 1;
            }
            // cout << "num_dead_cell: "<<num_dead_cell << endl;  // it is fine
            if (num_dead_cell == 11) {
                clean_row.push_back(row);
                
            }
        }
    }
    // for scoring
    int a = clean_row.size();
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < 11; ++j) {
            string color = pler->PlayField[clean_row[i]][j].GetColor();
            if (color == "I") {
                pler->IBlock += 1;
            } else if (color == "J") {
                pler->JBlock += 1;
            } else if (color == "L") {
                pler->LBlock += 1;
            } else if (color == "O") {
                pler->OBlock += 1;
            } else if (color == "S") {
                pler->SBlock += 1;
            } else if (color == "T") {
                pler->TBlock += 1;
            } else if (color == "Z") {
                pler->ZBlock += 1;
            }
        }
    }
    
    
    
    if (clean_row.size() != 0) {
        ClearLine(pler, clean_row);
    }
    return a;
}



void BiqBoard::ClearLine(shared_ptr <Player>& pler,  vector< int > & clean_row){
    vector < vector < Cell> > new_PlayField;
    int num_clean_row = clean_row.size();
    int x = 0;
    new_PlayField.resize(15);
    
    for (int row = 0; row < num_clean_row; row++) {
        new_PlayField[row].resize(11);
        for (int col = 0; col < 11; col++) {
            new_PlayField[row][col] = Cell();
            
        }
    }
    
    
    for (int row = 0; row < 15; row++) {
        if (row + x >= 15) {
            break;
        }
        
        if (clean_row.back() == row ) {
            clean_row.pop_back();
            x += 1;
            continue;
        } else {
            new_PlayField[row + num_clean_row - x].resize(11);
            
            
            for (int col = 0; col < 11; col++) {
                new_PlayField[row + num_clean_row - x][col] = pler->PlayField[row][col];
            }
        }
    }
    
    
    
    int add_score = (num_clean_row + pler->level)*(num_clean_row + pler->level);
    //cout << add_score << endl;
    
    if ((pler->IBlock != 0)&&(pler->IBlock % 4 == 0)) {
        add_score += 1;
    }
    if ((pler->JBlock != 0)&&(pler->JBlock % 4 == 0)) {
        add_score += 1;
    }
    if ((pler->LBlock != 0)&&(pler->LBlock % 4 == 0)) {
        add_score += 1;
    }
    if ((pler->OBlock != 0)&&(pler->OBlock % 4 == 0)) {
        add_score += 1;
    }
    if ((pler->SBlock != 0)&&(pler->SBlock % 4 == 0)) {
        add_score += 1;
    }
    if ((pler->TBlock != 0)&&(pler->TBlock % 4 == 0)) {
        add_score += 1;
    }
    
    cout << add_score << endl;
    pler->IBlock = 0;
    pler->JBlock = 0;
    pler->LBlock = 0;
    pler->OBlock = 0;
    pler->SBlock = 0;
    pler->TBlock = 0;
    
    pler->PlayField = new_PlayField;
    pler->Score += add_score;
    if (pler->High < pler->Score) {
        pler->High = pler->Score;
    }
}

// ********************** Level UP and Down **********************
void BiqBoard::LevelUp(shared_ptr <Player>& pler){
    int le = pler->level + 1;
    
    if(le == 1) {
        //unique_ptr <Level> temp = pler->levptr;
        pler->levptr= unique_ptr <Level> (new Level1);
        pler->level = 1;
        pler->staron = false;
        //delete temp;
        
    }else if (le == 2){
        //unique_ptr <Level> temp = pler->levptr;
        pler->levptr= unique_ptr <Level> (new Level2);
        pler->level = 2;
        pler->staron = false;
        //delete temp;
        
    }else if (le == 3){
        
        //unique_ptr <Level> temp = pler->levptr;
        pler->levptr= unique_ptr <Level> (new Level3);
        pler->level = 3;
        pler->staron = false;
        //delete temp;
        
    }else if (le == 4){
        
        //unique_ptr <Level> temp = pler->levptr;
        pler->levptr= unique_ptr <Level> (new Level4);
        pler->level = 4;
        pler->staron = true;
        //delete temp;
        
    }/*else if ((le == 5)&&(specialOn)){
        pler->levptr= unique_ptr <Level> (new Level5);
        pler->level = 5;
        pler->staron = false;
    }*/
    
    
}

void BiqBoard::LevelDown(shared_ptr <Player>& pler){
    
    int le = pler->level - 1;
    
    if(le == 1) {
        //unique_ptr <Level> temp = pler->levptr;
        pler->levptr= unique_ptr <Level> (new Level1);
        pler->level = 1;
        pler->staron = false;
        //delete temp;
        
    }else if (le == 2){
        //unique_ptr <Level> temp = pler->levptr;
        pler->levptr= unique_ptr <Level> (new Level2);
        pler->level = 2;
        pler->staron = false;
        //delete temp;
        
    }else if (le == 3){
        
        //unique_ptr <Level> temp = pler->levptr;
        pler->levptr= unique_ptr <Level> (new Level3);
        pler->level = 3;
        pler->staron = false;
        //delete temp;
        
    }else if (le == 0){
        
        //unique_ptr <Level> temp = pler->levptr;
        pler->levptr= unique_ptr <Level> (new Level0);
        pler->level = 0;
        pler->staron = false;
        //delete temp;
    }else if (le == 4){
        
        pler->levptr= unique_ptr <Level> (new Level4);
        pler->level = 4;
        pler->staron = true;
    }
    
}

// ********************** helper function to test **********************
void BiqBoard::SetDeadCell(shared_ptr <Player>& pler, int row1, int col1, int row2, int col2){
    int row_times = row2 - row1 ;
    int col_times = col2 - col1 ;
    
    
    for (int i = 0; i <= row_times ; ++i) {
        for (int j = 0; j <= col_times; ++j) {
            
            pler->PlayField[row1 + i][col1 + j].TurnOff("*");
        }
    }
}



void BiqBoard::KillLiveCell(shared_ptr <Player>& pler){
    for (int row = 0; row < 15; ++row){
        for (int col = 0; col < 11; ++col){
            Cell cur = pler->PlayField[row][col];
            if (cur.IsAlive()){
                pler->PlayField[row][col].TurnOff(" ");
            }
        }
    }
}





// ********************** Heavy **********************
void BiqBoard::LevelHeavy (shared_ptr <Player>& pler) {
    if ((pler->cant_down == 0)&&(pler->level >= 3)) {
        update(pler);
        down(pler);
        update(pler);
        
    }
}

void BiqBoard::BlockHeavy (shared_ptr <Player>& pler) {
    
    for (int i = 0; i < 2; ++i) {
        if ((pler->cant_down == 0)&&(pler->heavy)) {
            cout << "here is bu" << endl;
            update(pler);
            down(pler);
            update(pler);
        }
    }
}





// ********************** GameOver **********************
bool BiqBoard::GameOver (shared_ptr <Player>& pler) {
    string four0 = pler->PlayField[3][0].GetColor();
    bool four0bool = pler->PlayField[3][0].IsAlive();
    string four1 = pler->PlayField[3][1].GetColor();
    bool four1bool = pler->PlayField[3][1].IsAlive();
    string four2 = pler->PlayField[3][2].GetColor();
    bool four2bool = pler->PlayField[3][2].IsAlive();
    string four3 = pler->PlayField[3][3].GetColor();
    bool four3bool = pler->PlayField[3][3].IsAlive();
    string five0 = pler->PlayField[4][0].GetColor();
    bool five0bool = pler->PlayField[4][0].IsAlive();
    string five1 = pler->PlayField[4][1].GetColor();
    bool five1bool = pler->PlayField[4][1].IsAlive();
    string five2 = pler->PlayField[4][2].GetColor();
    bool five2bool = pler->PlayField[4][2].IsAlive();
    string five3 = pler->PlayField[4][3].GetColor();
    
    
    if ((pler->NextBlock->Type() == "I")&&
        (((four0 != " ") && (!four0bool)) ||
         ((four1 != " ") && (!four1bool)) ||
         ((four2 != " ") && (!four2bool)) ||
         ((four3 != " ") && (!four3bool)))){
            // cout << "I here" << endl;
            return false;
        }
    if ((pler->NextBlock->Type() == "O")&&
        (((four0 != " ") && (!four0bool))||
         ((four1 != " ") && (!four1bool))||
         ((five0 != " ") && (!five0bool))||
         ((five1 != " ") && (!five1bool)))){
            //cout << "O here" << endl;
            return false;
        }
    if ((pler->NextBlock->Type() == "T")&&
        (((four1 != " ") && (!four1bool))||
         ((five0 != " ") && (!five0bool))||
         ((five1 != " ") && (!five1bool))||
         ((five2 != " ") && (!five2bool)))){
            //cout << "T here" << endl;
            return false;
        }
    if ((pler->NextBlock->Type() == "L")&&
        (((four3 != " ") && (!four3bool))||
         ((five0 != " ") && (!five0bool))||
         ((five1 != " ") && (!five1bool))||
         ((five2 != " ") && (!five2bool)))){
            //cout << "L here" << endl;
            return false;
        }
    if ((pler->NextBlock->Type() == "J")&&
        (((four0 != " ") && (!four0bool))||
         ((five0 != " ") && (!five0bool))||
         ((five1 != " ") && (!five1bool))||
         ((five2 != " ") && (!five2bool)))){
            //cout << "J here" << endl;
            return false;
        }
    if ((pler->NextBlock->Type() == "Z")&&
        (((four0 != " ") && (!four0bool))||
         ((four1 != " ") && (!four1bool))||
         ((five1 != " ") && (!five1bool))||
         ((five2 != " ") && (!five2bool)))){
            //cout << "Z here" << endl;
            return false;
        }
    if ((pler->NextBlock->Type() == "S")&&
        (((four1 != " ") && (!four1bool))||
         ((four2 != " ") && (!four2bool))||
         ((five0 != " ") && (!five0bool))||
         ((five1 != " ") && (!five1bool)))){
            //cout << "S here" << endl;
            
            
            return false;
        }
    //cout << "end here" << endl;
    return true;
}

// ********************** Restart **********************
void BiqBoard::Restart(shared_ptr <Player>& pler1, shared_ptr <Player>& pler2){
    SetPler(pler1, "John" , 1, 0);
    SetPler(pler2, "AZ" , 2, 0);
    
}

void BiqBoard::Blind (shared_ptr <Player>& pler){
    for (int i = 2; i < 12; ++i){
        for (int j = 2; j < 9; ++j){
            pler->PlayField[i][j].
            TurnBlind();
        }
    }
}
