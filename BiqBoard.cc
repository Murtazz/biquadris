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
void BiqBoard::SetPler(shared_ptr <Player> &pler, string playername,int id,int curLev) {
    
    pler->PlayField.resize(15);
    for (int row = 0; row < 15; row++) {
        pler->PlayField[row].resize(11);
        for (int col = 0; col < 11; col++) {
            pler->PlayField[row][col] = Cell();
        }
    }
    //for curLev
    if (curLev == 0) {
        pler->levptr = unique_ptr <Level> (new Level0);
    } else if (curLev == 1) {
        pler->levptr = unique_ptr <Level> (new Level1);
    } else if (curLev == 2) {
        pler->levptr= unique_ptr <Level> (new Level2);
    } else if (curLev == 3) {
        pler->levptr= unique_ptr <Level> (new Level3);
    } else if (curLev == 4) {
        pler->levptr= unique_ptr <Level> (new Level4);
    } 
    
    
    pler->id = id;
    
    pler->CurBlock = nullptr;
    pler->NextBlock = nullptr;
    pler->name = playername;
    pler->Score = 0;
    pler->curLev = curLev;
    pler->Active = true;
    pler->SpeAttack = 0;
    pler->col = 0;
    pler->row = 0;
    pler->downImposs = 0;
    pler->LPoss = true;
    pler->RPoss = true;
    pler->DPoss = true;
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

// get players
shared_ptr <Player>& BiqBoard::Getpler1() {
    return pler1;
    
}

shared_ptr <Player>& BiqBoard::Getpler2() {
    return pler2;
}





// get score
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

// Making the board
void BiqBoard::DrawBoard(shared_ptr <Player>& pler1, shared_ptr <Player>& pler2, Xwindow * board) {
    int temp_col = 0;
    cout << "Level:    " << pler1->curLev << "     " << "Level:    " << pler2->curLev << endl;
    cout << "Score:    " << pler1->Score << "     " << "Score:    " << pler2->Score << endl;
    cout << "High :    " << pler1->High << "     " << "High :    " << pler2->High << endl;
    if (!IsText){
        board->fillRectangle(0, 0, 600, 30, 5);
        board->drawString(5, 25, "Level:", 7);
        string levelStr1 = NumToString(pler1->curLev);
        board->drawString(55, 25, levelStr1, 7);
        
        board->drawString(100, 25, "Score:", 7);
        string scoreStr1 = NumToString(pler1->Score);
        board->drawString(150, 25, scoreStr1, 7);
        
        board->drawString(200, 25, "High:", 7);
        string highStr1 = NumToString(pler1->High);
        board->drawString(250, 25, highStr1, 7);
        
        board->drawString(330, 25, "Level:", 7);
        string levelStr2 = NumToString(pler2->curLev);
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
                board->fillRectangle(j*25, i*25, 25, 25, 1);
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
                if (pler->downImposs == 1) {
                    pler->PlayField[new_row][new_col].TurnOff(color);
                    continue;
                }
                if (ava){
                    pler->PlayField[new_row][new_col].TurnOn(color);
                }
            }
        }
    }

    if (pler->downImposs == 1) {
        pler->downImposs = 0;
        pler->col = 0;
        pler->row = 0;
        pler->CurBlock = pler->NextBlock;
        pler->RPoss = true;
        pler->LPoss = true;
        pler->DPoss = true;
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





// switching

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





// command left
void BiqBoard::left(shared_ptr <Player>& pler){
    int player_col = pler->col;
    if ((player_col > 0)&&(pler->LPoss)){
        
        pler->col -= 1;
        pler->RPoss = true;
        pler->DPoss = true;
    }
    else {
        pler->RPoss = true;
        pler->LPoss = true;
        pler->DPoss = true;
    }
    pler->clockPossible = true;
    pler->counterCPossible = true;
}


// command right
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
    
    
    if ((player_col + require_col + 2 <= board_col) && (pler->RPoss)) {
        
        pler->col += 1;
        pler->LPoss = true;
        pler->DPoss = true;
        
    }
    else if (!pler->RPoss) {
        pler->RPoss = true;
        pler->LPoss = true;
        pler->DPoss = true;
    }
    pler->clockPossible = true;
    pler->counterCPossible = true;
}


// command down
void BiqBoard::down(shared_ptr <Player>& pler){
    int player_row = pler->row;
    if (!pler->DPoss) {
        ++pler->notclear;//
        //  cout << "can't down" << endl;
        pler->downImposs += 1;
        for (int i = 0; i < 15; ++i){
            for (int j = 0; j < 11; ++j){
                pler->PlayField[i][j].NotBlind();
            }
        }
    }
    
    if ((player_row < 15)&&(pler->DPoss)){
        pler->row += 1;
        pler->RPoss = true;
        pler->LPoss = true;
    } else {
        pler->RPoss = true;
        pler->LPoss = true;
        pler->DPoss = true;
    }
    pler->clockPossible = true;
    pler->counterCPossible = true;
    
}


// command drop
void BiqBoard::drop(shared_ptr <Player>& pler) {
    while (pler->downImposs == 0) {
        update(pler);
        down(pler);
        update(pler);
    }
}


// command cpossible
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
            
            vector <vector <string>> v_copy = copy->getBlock();
            string cwcolor = v_copy[row][col];
    
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


// command ccwpossible
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



// update possibilities
void BiqBoard::initialPossibilities () {
    pler1->DPoss = true;
    pler1->RPoss = true;
    pler1->LPoss = true;
    pler2->DPoss = true;
    pler2->RPoss = true;
    pler2->LPoss = true;
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
            } else {
                if ((new_col+1 > 10)||(pler->PlayField[new_row][new_col+1].GetColor() != " ")){
                    pler->RPoss = false;
                }
                if (check_row == 0) {
                    check_row += 1;
                    if ((new_col -1 < 0)|| (pler->PlayField[new_row][new_col-1].GetColor() != " ")){
                        pler->LPoss = false;
                    }
                }
                if ((new_row+1 >= 15) || (pler->PlayField[new_row+1][new_col].GetColor() != " ")){
                    pler->DPoss = false;
                }                
            }
        }
    }
    clockPossible(pler);
    counterCPossible(pler);
}

// checking if lines are complete
int BiqBoard::ReCalc(shared_ptr <Player>& pler) {
    vector < int > clean_row;
    for (int row = 14; row > 0 ; row-- ) {
        int num_dead_cell = 0;
        for (int col = 0; col < 11; ++col) {
            if (pler->PlayField[row][col].GetColor() == " ") {
                continue;
            }
            else if ((!pler->PlayField[row][col].isActive())&&(pler->PlayField[row][col].GetColor() != " ")) {
                num_dead_cell += 1;
            }
            if (num_dead_cell == 11) {
                clean_row.push_back(row);
            }
        }
    }
    // score
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
        destroyLine(pler, clean_row);
    }
    return a;
}


// adding score and destroying lines
void BiqBoard::destroyLine(shared_ptr <Player>& pler,  vector< int > & clean_row){
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
    
    
    
    int add_score = (num_clean_row + pler->curLev)*(num_clean_row + pler->curLev);
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

// leveling up and down
void BiqBoard::LevelUp(shared_ptr <Player>& pler){
    int le = pler->curLev + 1;
    if (le == 1) {
        pler->levptr= unique_ptr <Level> (new Level1);
        pler->curLev = 1;
        pler->starblk = false;
    } else if (le == 2) {
        pler->levptr= unique_ptr <Level> (new Level2);
        pler->curLev = 2;
        pler->starblk = false;
    } else if (le == 3) {
        pler->levptr= unique_ptr <Level> (new Level3);
        pler->curLev = 3;
        pler->starblk = false;
    } else if (le == 4) {
        pler->levptr= unique_ptr <Level> (new Level4);
        pler->curLev = 4;
        pler->starblk = true;
    }
}

void BiqBoard::LevelDown(shared_ptr <Player>& pler) {
    int le = pler->curLev - 1;
    if (le == 1) {
        pler->levptr= unique_ptr <Level> (new Level1);
        pler->curLev = 1;
        pler->starblk = false;
    } else if (le == 2) {
        pler->levptr= unique_ptr <Level> (new Level2);
        pler->curLev = 2;
        pler->starblk = false;  
    } else if (le == 3) {
        pler->levptr= unique_ptr <Level> (new Level3);
        pler->curLev = 3;
        pler->starblk = false;
    }  else if (le == 4) {
        pler->levptr= unique_ptr <Level> (new Level4);
        pler->curLev = 4;
        pler->starblk = true;
    } else if (le == 0) {
        pler->levptr= unique_ptr <Level> (new Level0);
        pler->curLev = 0;
        pler->starblk = false;
    }
}

void BiqBoard::deadCell(shared_ptr <Player>& pler) {
    for (int row = 0; row < 15; ++row){
        for (int col = 0; col < 11; ++col){
            Cell cur = pler->PlayField[row][col];
            if (cur.isActive()){
                pler->PlayField[row][col].TurnOff(" ");
            }
        }
    }
}

// Heavy
void BiqBoard::LevelHeavy(shared_ptr <Player>& pler) {
    if ((pler->downImposs == 0)&&(pler->curLev >= 3)) {
        update(pler);
        down(pler);
        update(pler);
    }
}

void BiqBoard::BlockHeavy(shared_ptr <Player>& pler) {
    for (int i = 0; i < 2; ++i) {
        if ((pler->downImposs == 0)&&(pler->heavy)) {
            update(pler);
            down(pler);
            update(pler);
        }
    }
}


// when someone loses
bool BiqBoard::GameOver(shared_ptr <Player>& pler) {
    string four0 = pler->PlayField[3][0].GetColor();
    bool four0bool = pler->PlayField[3][0].isActive();
    string four1 = pler->PlayField[3][1].GetColor();
    bool four1bool = pler->PlayField[3][1].isActive();
    string four2 = pler->PlayField[3][2].GetColor();
    bool four2bool = pler->PlayField[3][2].isActive();
    string four3 = pler->PlayField[3][3].GetColor();
    bool four3bool = pler->PlayField[3][3].isActive();
    string five0 = pler->PlayField[4][0].GetColor();
    bool five0bool = pler->PlayField[4][0].isActive();
    string five1 = pler->PlayField[4][1].GetColor();
    bool five1bool = pler->PlayField[4][1].isActive();
    string five2 = pler->PlayField[4][2].GetColor();
    bool five2bool = pler->PlayField[4][2].isActive();
    string five3 = pler->PlayField[4][3].GetColor();
    
    if ((pler->NextBlock->Type() == "I")&&
        (((four0 != " ") && (!four0bool)) ||
         ((four1 != " ") && (!four1bool)) ||
         ((four2 != " ") && (!four2bool)) ||
         ((four3 != " ") && (!four3bool)))) {
            return false;
    }
    if ((pler->NextBlock->Type() == "O")&&
        (((four0 != " ") && (!four0bool))||
         ((four1 != " ") && (!four1bool))||
         ((five0 != " ") && (!five0bool))||
         ((five1 != " ") && (!five1bool)))) {
            return false;
    }
    if ((pler->NextBlock->Type() == "T")&&
        (((four1 != " ") && (!four1bool))||
         ((five0 != " ") && (!five0bool))||
         ((five1 != " ") && (!five1bool))||
         ((five2 != " ") && (!five2bool)))) {
        return false;
    }
    if ((pler->NextBlock->Type() == "L")&&
        (((four3 != " ") && (!four3bool))||
         ((five0 != " ") && (!five0bool))||
         ((five1 != " ") && (!five1bool))||
         ((five2 != " ") && (!five2bool)))) {
            return false;
    }
    if ((pler->NextBlock->Type() == "J")&&
        (((four0 != " ") && (!four0bool))||
         ((five0 != " ") && (!five0bool))||
         ((five1 != " ") && (!five1bool))||
         ((five2 != " ") && (!five2bool)))) {
            return false;
    }
    if ((pler->NextBlock->Type() == "Z") &&
        (((four0 != " ") && (!four0bool))||
         ((four1 != " ") && (!four1bool))||
         ((five1 != " ") && (!five1bool))||
         ((five2 != " ") && (!five2bool)))) {
            return false;
    }
    if ((pler->NextBlock->Type() == "S") &&
        (((four1 != " ") && (!four1bool))||
        ((four2 != " ") && (!four2bool))||
        ((five0 != " ") && (!five0bool))||
        ((five1 != " ") && (!five1bool)))) {
        return false;
    }
    return true;
}

//To restart the game
void BiqBoard::Restart(shared_ptr <Player>& pler1, shared_ptr <Player>& pler2) {
    SetPler(pler1, "Murtaza" , 1, 0);
    SetPler(pler2, "Qianli" , 2, 0);
}


// blind
void BiqBoard::Blind(shared_ptr <Player>& pler) {
    for (int i = 2; i < 12; ++i) {
        for (int j = 2; j < 9; ++j) {
            pler->PlayField[i][j].TurnBlind();
        }
    }
}
