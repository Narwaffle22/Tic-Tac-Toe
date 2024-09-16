// tic-tac-toe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>

using namespace std;

class Board {
public:
    Board();
    string getBoard();

private:
    string currentBoard;
    string slots[9] = { "1","2","3","4","5","6","7","8","9" };
    string startingBoard = "   |   |   \n-- - +-- - +-- - \n   |   |   \n-- - +-- - +-- - \n   |   |   ";
};

Board::Board() {
    this->currentBoard = startingBoard;
}
Board::getBoard() {
    return currentBoard;
}

class Boardprinter {
public:
    Boardprinter();

private:
    string something;
    string edgeMarker = " ";
    string verticalDivider = " | ";
    string horizontalDivider = "\n---+---+---\n";
};



Boardprinter::Boardprinter() {
    this->something = " ";
}

int main()
{
    Board* board = new Board();

}