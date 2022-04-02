#include "Draw.h"
using namespace std;



void drawPx(int a, int b, Xwindow& board){
    int x = 10;
    int y = 50;
    int w = 16;
    int c = 9;
    
    board.fillRectangle(x + w*a, y + w*b  ,w , w , c);
    
}


void drawMainBoard(Xwindow &board, bool sound) {
    

    std::string s1;

    int bg = 6;
    //Coverpage
    while(1){
        //we end(actually start game here)
        
        //background
        board.fillRectangle( 0 , 0 , 600 , 550 , bg);
        
        //title
        
        //b
        
        //drawPx(0,-1,board);
        drawPx(3,0,board);
        drawPx(3,1,board);
        drawPx(3,2,board);
        drawPx(3,3,board);
        drawPx(3,4,board);
        drawPx(3,5,board);
        drawPx(3,6,board);
        //drawPx(0,6,board);
        drawPx(4,6,board);
        drawPx(5,6,board);
        //drawPx(4,6,board);
        //drawPx(5,6,board);
        drawPx(5,5,board);
        drawPx(5,4,board);
        //drawPx(3,3,board);
        //drawPx(3,3,board);
        drawPx(4,4,board);
        //drawPx(4,2,board);
        //drawPx(2,3,board);
        //drawPx(4,1,board);
        //drawPx(4,0,board);
        //drawPx(3,0,board);
        //drawPx(2,0,board);
        
        //i
        
        drawPx(7,2,board);
        //drawPx(6,3,board);
        drawPx(7,4,board);
        drawPx(7,5,board);
        drawPx(7,6,board);
        
        //q
        
        //drawPx(12,3,board);
        drawPx(11,4,board);
        drawPx(10,4,board);
        drawPx(9,4,board);
        drawPx(9,5,board);
        drawPx(9,6,board);
        drawPx(10,6,board);
        drawPx(11,5,board);
        drawPx(11,6,board);
        drawPx(11,7,board);
        drawPx(11,8,board);
        //drawPx(12,9,board);
        
        //u
        
        drawPx(13,4,board);
        drawPx(13,5,board);
        drawPx(13,6,board);
        drawPx(14,6,board);
        drawPx(15,6,board);
        drawPx(15,5,board);
        drawPx(15,4,board);
        
        //a
        
        //drawPx(20,3,board);
        //drawPx(19,4,board);
        drawPx(18,4,board);
        //drawPx(17,4,board);
        drawPx(17,5,board);
        //drawPx(17,6,board);
        drawPx(18,6,board);
        drawPx(19,6,board);
        drawPx(19,5,board);
        //drawPx(20,7,board);
        
        //d
        drawPx(22,4,board);
        drawPx(21,4,board);
        drawPx(21,5,board);
        drawPx(21,6,board);
        drawPx(22,6,board);
        drawPx(23,1,board);
        drawPx(23,2,board);
        drawPx(23,3,board);
        drawPx(23,4,board);
        drawPx(23,5,board);
        drawPx(23,6,board);
        //drawPx(24,7,board);
        
        
        //r
        drawPx(25,4,board);
        drawPx(26,5,board);
        drawPx(26,6,board);
        //drawPx(26,4,board);
        drawPx(27,4,board);
        
        //i
        drawPx(29,2,board);
        //drawPx(28,3,board);
        drawPx(29,4,board);
        drawPx(29,5,board);
        drawPx(29,6,board);
        
        //s
        drawPx(33,3,board);
        drawPx(32,3,board);
        drawPx(31,4,board);
        //drawPx(31,5,board);
        drawPx(32,5,board);
        drawPx(33,6,board);
        drawPx(32,7,board);
        drawPx(31,7,board);
        

            
        string line1 = "Welcome to two players biquadris!";
        string line2 = "Here are some of the rules:";
        string line3 = "To control the blockes by commends with (-easy)";
        string line4 = "right(d), left(a), down(s), drop(ss), levelup(q), leveldown(e),";
        string line5 = "clockwise(cw) and counterclockwise(ccw).";
        string line6 = "Have fun! ";

        board.drawString( 100 , 250 , line1,4);
        board.drawString( 100 , 280 , line2,4);
        board.drawString( 100 , 310 , line3,4);
        board.drawString( 100 , 340 , line4,4);
        board.drawString( 100 , 370 , line5,4);
        board.drawString( 100 , 400 , line6,4);
        
        //hint
        string c = "Press anykey to continue! ";
        board.drawString(180 , 530  , c);
        
        
        
        if(cin >> s1) break;
    }
    
   
    /*
    while(1){
        //here is about the rules
        board.fillRectangle( 0 , 0 , 600 , 550 , bg);
        
        //words
        

    //    std::string line8 = "test ";
    //    board.drawString( 80 , 450 , line8,4);

// board.drawString( 400 , 550 , s);

       
        //
        string r = "Press anykey to start /(* ` b `)/";
        board.drawString( 175 , 530  , r);
        
        if(std::cin >> s1) break;
    }
    */
    
  board.fillRectangle( 0 , 0 , 600 , 550 , bg);
}