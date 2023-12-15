/* -----------------------------------------------------------------------------------
Program 7: Outlast the Baddies & Avoid the Abyss
Author: Zeehan Sharif
Course: CS211, Fall 2023, UIC
System: Advanced zyLab
------------------------------------------------------------------------------------- */
#ifndef _GAMEBOARD_H
#define _GAMEBOARD_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>

#include "boardcell.h"
#include "grid.h"

using namespace std;

class GameBoard {
	private: 
	    Grid<BoardCell*> board;
        size_t numRows;
        size_t numCols;
        size_t HeroRow; // Hero's position row
	    size_t HeroCol; // Hero's position column
        int numMonsters;
        int numSuperMonsters;
        int numAbysses;
        int numBats;
        bool wonGame; // false, unless the Hero reached the exit successfully

		
	public: 
		/* default constructor */
        GameBoard() {
            numMonsters = 4;
            numSuperMonsters = 2;
            numAbysses = 50;
            numBats = 2;
            wonGame = false;
            
            this -> numRows = 15;
            this -> numCols = 40;
            
            Grid<BoardCell*> boardnew(numRows, numCols);
            board = boardnew;
            
            blankBoard();
        }
        
        /* param constructor */
        GameBoard(size_t numRows, size_t numCols) {
            numMonsters = 4;
            numSuperMonsters = 2;
            numAbysses = 20;
            numBats = 3;
            wonGame = false;
            
            this -> numRows = numRows;
            this -> numCols = numCols;
            
            Grid<BoardCell*> boardnew(numRows, numCols);
            board = boardnew;
            
            blankBoard();
        }
        
        /* destructor */
        virtual ~GameBoard() {
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    delete board(row, col);
                }
            }
        }

        void blankBoard() {
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    board(row, col) = new Nothing(row,col);
                }
            }
        }

        char getCellDisplay(size_t r, size_t c) {
            return board(r,c)->display();
        }

        void setCell(BoardCell* myCell, size_t r, size_t c) {
            board(r,c) = myCell;
        }
    
        void freeCell(size_t r, size_t c) {
            delete board(r,c);
        }

        // fills board with by randomly placing...
        //  - Hero (H) in the first three columns
        //  - EscapeLadder (*) in last three columns
        //  - 3 vertical Walls (+), each 1/2 of board height, in middle segment
        //  - Abyss cells (#), quantity set by numAbysses, in middle segment
        //  - Baddies [Monsters (m), Super Monsters (M), & Bats (~)] in middle segment;
        //    number of Baddies set by numMonsters, numSuperMonsters, & numBats
        void setupBoard(int seed) {
            srand(seed);
            size_t r,c;

            r = rand() % numRows;
            c = rand() % 3;
            delete board(r,c);
            board(r,c) = new Hero(r,c);
            HeroRow = r;
            HeroCol = c;

            r = rand() % numRows;
            c = numCols - 1 - (rand() % 3);
            delete board(r,c);
            board(r,c) = new EscapeLadder(r,c);
            
            int sizeMid = numCols - 6;

            c = 3 + (rand() % sizeMid);
            for (r = 0; r < numRows/2; ++r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);
            }
            size_t topc = c;

            while (c == topc || c == topc-1 || c == topc+1) {
                c = 3 + (rand() % sizeMid);
            }
            for (r = numRows-1; r > numRows/2; --r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);           
            }
            size_t botc = c;

            while (c == topc || c == topc-1 || c == topc+1 || c == botc || c == botc-1 || c == botc+1) {
                c = 3 + (rand() % sizeMid);
            }
            for (r = numRows/4; r < 3*numRows/4; ++r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);
            }

            for (int i = 0; i < numMonsters; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Monster(r,c);  
                board(r,c)->setPower(1);        
            }

            for (int i = 0; i < numSuperMonsters; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Monster(r,c); 
                board(r,c)->setPower(2);               
            }

            for (int i = 0; i < numBats; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Bat(r,c); 
            }

            for (int i = 0; i < numAbysses; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Abyss(r,c);              
            }
        }

        // neatly displaying the game board 
		void display( ) {
            cout << '-';
            for (size_t col = 0; col < board.numcols(0); col++) {
                cout << '-';
            }
            cout << '-';
            cout << endl;
            for (size_t row = 0; row < board.numrows(); row++) {
                cout << '|';
                for (size_t col = 0; col < board.numcols(row); col++) {
                    cout << board(row,col)->display();
                }
                cout << '|';
                cout << endl;
            }
            cout << '-';
            for (size_t col = 0; col < board.numcols(0); col++) {
                cout << '-';
            }
            cout << '-';
            cout << endl;
            
        }
		
        bool getWonGame() {
            return wonGame;
        }
        
        // distributing total number of monsters so that 
        //  ~1/3 of num are Super Monsters (M), and
        //  ~2/3 of num are Regular Monsters (m)
        void setNumMonsters(int num) {
            numSuperMonsters = num/3;
            numMonsters = num - numSuperMonsters;
        }

        void setNumAbysses(int num) {
            numAbysses = num;
        }

        void setNumBats(int num) {
            numBats = num;
        }

        size_t getNumRows() {
            return numRows;
        }

        size_t getNumCols() {
            return numCols;
        }

        
        //---------------------------------------------------------------------------------
        // getter for Hero's position, which are private data members
        //      int HeroRow;
	    //      int HeroCol;
        // note: row and col are passed-by-reference
        //---------------------------------------------------------------------------------
        void getHeroPosition(size_t& row, size_t& col) {
            row = HeroRow;  // modify/remove this line
            col = HeroCol;  // modify/remove this line
        }
        
        //---------------------------------------------------------------------------------
        // setter for Hero's position, which are private data members
        //      int HeroRow;
	    //      int HeroCol;
        //---------------------------------------------------------------------------------
        void setHeroPosition(size_t row, size_t col) {
            HeroRow = row;
            HeroCol = col;
        }

        //---------------------------------------------------------------------------------
        // updater for Hero's position, which are private data members
        //      int HeroRow;
	    //      int HeroCol;
        // this function should find Hero in board and update
        //      HeroRow and HeroCol with the Hero's updated position;
        // if Hero cannot be found in board, then set Hero's position to (-1,-1)
        //---------------------------------------------------------------------------------
        void findHero() {

            for(size_t i = 0; i < numRows; i++){

                for(size_t j = 0; j < numCols; j++){

                    if(board(i,j)->isHero()){

                        HeroRow = i;
                        HeroCol = j;
                        return;
                    }
                }
            }

            HeroRow = -1;
            HeroCol = -1;
        }

        //---------------------------------------------------------------------------------
        //The parameters are HeroNextMove, which is what the hero's next move is in char
        //Summary: It constantly updates the Hero's position based on every input and how the baddies move as well. It also resolves collisions and ensures the baddies only move onve per round. Also reset the the statuses for all board cells.
        //Returns true if the hero is still on the board at the end of the round, and false if the hero is not on the board anymore
        //---------------------------------------------------------------------------------
        bool makeMoves(char HeroNextMove) {

            size_t newRow, newCol;
            bool endGame = false;
            board(HeroRow, HeroCol)->setNextMove(HeroNextMove);
            board(HeroRow, HeroCol)->attemptMoveTo(newRow, newCol, HeroRow, HeroCol);

            //hero moving out of bounds in a column
            try{
                
                if(newCol < 0 || newCol >= numCols){
                    throw runtime_error("Hero trying to move out-of-bounds with an invalid column");
                }
            }
            catch(const runtime_error &e) { //catch the error

                cout << e.what() << endl;
                newCol = HeroCol;
                cout << "Changing column for Hero position to stay in-bounds" << endl;
            }

            //hero moving out of bounds in row
            try{

                if(newRow < 0 || newRow >= numRows){
                    throw runtime_error("Hero trying to move out-of-bounds with an invalid row");
                }
            }
            catch(const runtime_error &e) { //catch the error

                cout << e.what() << endl;
                newRow = HeroRow;
                cout << "Changing row for Hero position to stay in-bounds" << endl;
            }

            //when a hero accidentaly moves into a barrier
            try{

                if(board(newRow, newCol)->isBarrier()){
                    throw runtime_error("Hero trying to move into a barrier");
                }
            }
            catch(runtime_error &e){ //catch the error

                cout << e.what() << endl;
                newCol = HeroCol;
                cout << "Changing Hero position to stay off barrier" << endl;
            }

            //Hero runs into a baddie or a black hole
            try{

                if(board(newRow, newCol)->isHole() || board(newRow, newCol)->isBaddie()){
                    throw runtime_error("Uh Oh! Hero has moved into a Baddie or the Abyss...");
                }
            }
            catch(const runtime_error &e){ //catch the error

                cout << e.what() << endl;
                cout << "Be more careful next time..." << endl;
                delete board(HeroRow, HeroCol);
                board(HeroRow, HeroCol) = new Nothing(HeroRow, HeroCol);
                this->wonGame = false;
                return false;
            }

            //if the hero hits a ladder for exit
            if(board(newRow, newCol)->isExit()){

                cout << "Hero has reached the exit!\nHero has escaped!" << endl;
                delete board(HeroRow, HeroCol);
                board(HeroRow, HeroCol) = new Nothing(HeroRow, HeroCol);
                this->wonGame = true;
                return false;
            }

            //remove the hero from the board, and move the hero to newRow and newCol
            delete board(HeroRow, HeroCol);
            board(HeroRow, HeroCol) = new Nothing(HeroRow, HeroCol);

            delete board(newRow, newCol);
            board(newRow, newCol) = new Hero(newRow, newCol);

            //set the hero's new postion after moving again
            setHeroPosition(newRow, newCol);

            //reset the board setMoved item to setup
            for(size_t row = 0; row < numRows; row++){

                for(size_t col = 0; col < numCols; col++){

                    if(board(row, col)->isBaddie()){
                        board(row, col)->setMoved(false);
                    }
                }
            }

            //Update the moves for every other baddie
            for(size_t row = 0; row < numRows; row++){

                for(size_t col = 0; col < numCols; col++){

                    size_t newRow = row;
                    size_t newCol = col;

                    if(!board(row, col)->isBaddie() || board(row, col)->getMoved()){
                        continue;
                    }

                    //try to move the baddies
                    board(row, col)->attemptMoveTo(newRow, newCol, HeroRow, HeroCol);

                    //check columns edge
                    if(newCol < 0 || newCol >= numCols){
                        newCol = col;
                    }

                    //check row edge
                    if(newRow < 0 || newRow >= numRows){
                        newRow = row;
                    }

                    //see if baddie hit exit
                    if(board(newRow, newCol)->isExit()){

                        newCol = col;
                        newRow = row;
                    }

                    //see if baddie hit barrier
                    if(board(newRow, newCol)->isBarrier()){
                        newCol = col;
                    }

                    //see if baddie fell down a hole
                    if(board(newRow, newCol)->isHole()){

                        delete board(row, col);
                        board(row, col) = new Nothing(row, col);
                        continue;
                    }

                    //see if the baddie beats another baddie
                    if(board(newRow, newCol)->isBaddie()){

                        newRow = row;
                        newCol = col;
                    }

                    //see if baddie eats hero
                    if(board(newRow, newCol)->isHero()){
                        endGame = true;
                    }

                    char typeOfBaddie = board(row, col)->display();
                    delete board(row,col);

                    //Get the the baddies out of board
                    board(row, col) = new Nothing(row, col);
                    delete board(newRow, newCol);

                    //change position for baddies based on type
                    if(typeOfBaddie == '~'){

                        board(newRow, newCol) = new Bat(newRow, newCol);
                        board(newRow, newCol)->setMoved(true);                  
                    }
                    else if(typeOfBaddie == 'M'){

                        board(newRow, newCol) = new Monster(newRow, newCol);
                        board(newRow, newCol)->setPower(2);
                        board(newRow, newCol)->setMoved(true);
                    }
                    else if(typeOfBaddie == 'm'){

                        board(newRow, newCol) = new Monster(newRow, newCol);
                        board(newRow, newCol)->setPower(1);
                        board(newRow, newCol)->setMoved(true);
                    }
                }
            }

            //check if game is over/lost
            if(endGame){

                this->wonGame = false;
                return false;
            }

            return true;
        }
};

#endif //_GAMEBOARD_H