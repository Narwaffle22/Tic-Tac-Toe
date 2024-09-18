// tic-tac-toe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include <string>

using namespace std;

#pragma region Rules Class
class Rules
{
public:
    Rules();
    bool verifyInput(string,string);

private:
    bool checkCorrectCharacter(string);
    bool isInRange(int);
};

Rules::Rules()
{
}
bool Rules::verifyInput(string space, string token) {
    bool correctToken = true;
    int mark;
    
    correctToken = checkCorrectCharacter(token);
    if (isdigit(stoi(space))) {
        mark = stoi(space);
        correctToken = isInRange(mark);
    } else {
        correctToken = false;
    }

    return correctToken;
}
bool Rules::checkCorrectCharacter(string token) {
    if (token == "X" || token == "O") {
        return true;
    } else {
        return false;
    }
}
bool Rules::isInRange(int space) {
    if (space < 0 && space < 10) {
        return true;
    } else {
        return false;
    }
}

#pragma endregion

#pragma region Board Class

class Board {
public:
    Board();
    string getBoard();
    void markBoard(int, string);
    string checkTile(int);
    void printBoard();

private:
    string currentBoard;
    string slots[9] = { "1","2","3","4","5","6","7","8","9" };
    string startingBoard = " 1 | 2 | 3 \n---+---+---\n 4 | 5 | 6 \n---+---+---\n 7 | 8 | 9 ";
    string edgeMarker = " ";
    string verticalDivider = " | ";
    string horizontalDivider = "\n---+---+---\n";
    void formatBoard();
    Rules *ruleschecker = new Rules();
};

Board::Board() {
    this->currentBoard = startingBoard;
}
string Board::getBoard() {
    return currentBoard;
}
void Board::markBoard(int slot, string token) {
    slots[slot - 1] = token;
    
    formatBoard();
}
string Board::checkTile(int slot) {
    return "";
}
void Board::formatBoard() {
    currentBoard = edgeMarker + slots[0] + verticalDivider + slots[1] + verticalDivider + slots[2] + edgeMarker;
    currentBoard += horizontalDivider;
    currentBoard += edgeMarker + slots[3] + verticalDivider + slots[4] + verticalDivider + slots[5] + edgeMarker;
    currentBoard += horizontalDivider;
    currentBoard += edgeMarker + slots[6] + verticalDivider + slots[7] + verticalDivider + slots[8] + edgeMarker;
}
void Board::printBoard() {
    cout << currentBoard << "\n\n\n";
}

#pragma endregion

#pragma region Game Loop

class Game
{
public:
    Game();
    void start();
private:

};

Game::Game()
{
}
void Game::start() {
    Board* board = new Board();
    Rules* rules = new Rules();
    string input = "";
    int mark;
    bool canContinue = false;

    board->printBoard();

    cout << "let's do this thing!\n";
    while (!canContinue) {
        cout << "make your move\n";
        getline(cin, input);
    
        if (rules->verifyInput(input, "X")) {
            mark = stoi(input);
            cout << "\n";
            canContinue = true;
        }
    }
    

    board->markBoard(mark, "X");
    board->printBoard();

    cout << "now it's player two\n";
    getline(cin, input);
    mark = stoi(input);
    cout << "\n";
    
    board->markBoard(mark, "O");
    board->printBoard();
    

}

#pragma endregion

// main 
int main()
{
    Game* game = new Game();

    game->start();

}