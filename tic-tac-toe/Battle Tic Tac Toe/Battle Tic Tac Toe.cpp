#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;

#pragma region Rules Class
class Rules
{
public:
    Rules();
    bool verifyInput(string, string);
    bool isDone();
    bool checkCorrectCharacterBattle(string);
private:
    string mockBoard[9] = { "1","2","3","4","5","6","7","8","9" };
    string allowedBattleTokens[59]{ "?","!","*","~","$","%","#","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z" };
    int mockTurnCounter = 0;
    int winningCombos[9][3];
    bool checkCorrectCharacter(string);
    bool isInRange(int);
    bool isInteger(const string&);
    bool isAvailble(int);
    bool threeInARow(int, int, int);
    string XorO;
};

Rules::Rules(){
    winningCombos[0][0] = 0;
    winningCombos[0][1] = 1;
    winningCombos[0][2] = 2;

    winningCombos[1][0] = 3;
    winningCombos[1][1] = 4;
    winningCombos[1][2] = 5;

    winningCombos[2][0] = 6;
    winningCombos[2][1] = 7;
    winningCombos[2][2] = 8;

    winningCombos[3][0] = 0;
    winningCombos[3][1] = 3;
    winningCombos[3][2] = 6;

    winningCombos[4][0] = 1;
    winningCombos[4][1] = 4;
    winningCombos[4][2] = 7;

    winningCombos[5][0] = 2;
    winningCombos[5][1] = 5;
    winningCombos[5][2] = 8;

    winningCombos[6][0] = 0;
    winningCombos[6][1] = 4;
    winningCombos[6][2] = 8;

    winningCombos[7][0] = 2;
    winningCombos[7][1] = 4;
    winningCombos[7][2] = 6;
}
bool Rules::verifyInput(string space, string token) {
    bool correctToken = true;
    bool correctSpace = true;
    int mark;

    //correctToken = checkCorrectCharacter(token);

    if (isInteger(space)) {
        mark = stoi(space);
        correctSpace = isInRange(mark);
        correctSpace = isAvailble(mark);
    }
    else {
        correctSpace = false;
    }

    return correctToken && correctSpace;
}
bool Rules::checkCorrectCharacter(string token) {
    if (token == "X" || token == "O") {
        return true;
    }
    else {
        return false;
    }
}
bool Rules::isInRange(int space) {
    if (space > 0 && space < 10) {
        return true;
    }
    else {
        return false;
    }
}
bool Rules::isInteger(const string& str) {
    istringstream iss(str);
    int num;
    char extra;

    if (!(iss >> num) || (iss >> extra)) {
        return false;
    }

    return true;
}
bool Rules::isAvailble(int space) {
    if (mockTurnCounter % 2 == 0)
        XorO = "X";
    else
        XorO = "O";
    if ((mockBoard[space - 1] != "X" && mockBoard[space - 1] != "O") && isInRange(space)) {
        mockBoard[space - 1] = XorO;
        mockTurnCounter++;
        return true;
    } else {
        return false;
    }
}
bool Rules::isDone() {
    for (int i = 0; i < 8; i++) {
        if (this->threeInARow(winningCombos[i][0], winningCombos[i][1], winningCombos[i][2])) {
            cout << "Game is over, " << XorO << " wins\nPress [Enter] to continue";
            return true;
        }
    }

    for (int i = 0; i <= 8; i++) {
        if (isInteger(mockBoard[i]))
            return false;
    }

    cout << "Game is over, it's a tie, womp womp\nPress [Enter] to continue";
    return true;
}
bool Rules::threeInARow(int indexOne, int indexTwo, int indexThree) {
    return mockBoard[indexOne] == mockBoard[indexTwo] && mockBoard[indexTwo] == mockBoard[indexThree];
}
bool Rules::checkCorrectCharacterBattle(string token) {
    bool isAllGood = false;

    for (int i = 0; i < allowedBattleTokens->length()-1; i++) {
        if (token == allowedBattleTokens[i])
            isAllGood = true;
    }

    return isAllGood;
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
    Rules* ruleschecker = new Rules();
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
    return slots[slot];
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
    void startBattle();
private:
    int playerPlay(Rules*, string);
};

Game::Game() {
}
void Game::start() {
    Board* board = new Board();
    Rules* rules = new Rules();
    int mark;
    bool gameInPlay = true;

    while (gameInPlay) {
        board->printBoard();

        cout << "let's do this thing!\n";
        mark = playerPlay(rules, "X");

        board->markBoard(mark, "X");
        board->printBoard();
        if (rules->isDone()) {
            gameInPlay = false;
            continue;
        }

        cout << "now it's player two\n";
        mark = playerPlay(rules, "O");

        board->markBoard(mark, "O");
        board->printBoard();

        if (rules->isDone()) {
            gameInPlay = false;
            continue;
        }
    }
    string nothing;
    getline(cin, nothing);
}
void Game::startBattle() {
    Board* board = new Board();
    Rules* rules = new Rules();
    string p1Token, p2Token, input;
    int mark;
    bool gameInPlay = true;

    cout << "(The vaild tokens are as follows: A � Z, a � z, ?, !, *, ~, $, %, and #)\nPlayer One, please type what character yuo want to use:\n";
    getline(cin, input);
    while (!rules->checkCorrectCharacterBattle(input)) {
        cout << "\nNot quite, Remember the valid ones are: A � Z, a � z, ?, !, *, ~, $, %, and #, try again:\n";
        getline(cin, input);
    }
    p1Token = input;
    cout << "\nAlright, now Player Two, type yours:\n";
    getline(cin, input);
    while (!rules->checkCorrectCharacterBattle(input)) {
        cout << "\nNot quite, Remember the valid ones are: A � Z, a � z, ?, !, *, ~, $, %, and #, try again:\n";
        getline(cin, input);
    }
    p2Token = input;

    while (gameInPlay) {
        board->printBoard();

        cout << "let's do this thing!\n";
        mark = playerPlay(rules, p1Token);

        board->markBoard(mark, p1Token);
        board->printBoard();
        if (rules->isDone()) {
            gameInPlay = false;
            continue;
        }

        cout << "now it's player two\n";
        mark = playerPlay(rules, p2Token);

        board->markBoard(mark, p2Token);
        board->printBoard();

        if (rules->isDone()) {
            gameInPlay = false;
            continue;
        }
    }
    string nothing;
    getline(cin, nothing);
}
int Game::playerPlay(Rules* rules, string token) {
    string input = "";
    int mark = 0;
    bool canContinue = false;

    while (!canContinue) {
        cout << "make your move\n";
        getline(cin, input);

        if (rules->verifyInput(input, token)) {
            mark = stoi(input);
            cout << "\n";
            canContinue = true;
        }
        else {
            cout << "\nnot quite try again\n";
        }
    }
    return mark;
}
#pragma endregion

#pragma region Menu Class

class MainMenu {
public:
    MainMenu();
    void startTheProgram();
private:
    string welcomeMessages[3] = { "welcome back to the menu", "aaand we're back", "here we are again" };
    int randWelcome;
    void playTicTacToe();
    void playBatTicTacToe();
    void compendium();
    void statsScreen();
    void clearConsole();
    void randWelcomer();
};
MainMenu::MainMenu() {
}
void MainMenu::startTheProgram() {
    int command;
    bool inProgress = true;

    cout << "+--------------------------------------+" << "\n";
    cout << "+    Welcome to Battle Tic-Tac-Toe     +" << "\n";
    cout << "+--------------------------------------+" << "\n\n";

    cout << "Follow The Instructions to Navigate!\n" << endl;

    cout << "[1] Original Tic-Tac-Toe" << endl;
    cout << "[2] Battle Tic-Tac-Toe" << endl;
    cout << "[3] Archetypes Compendium (WIP)" << endl;
    cout << "[4] Show Stats from this Session (WIP)" << endl;
    cout << "[0] Exit" << endl;

    cout << "SELECT Command: ";
    cin >> command;

    while (inProgress) {
        randWelcomer();
        switch (command) {
        case 0: {
            inProgress = false;
            clearConsole();
            cout << "Hope you play again soon! see ya!";
            break;
        }
        case 1: {
            playTicTacToe();
            cout << "What a nice bit of nostalgia, " << welcomeMessages[randWelcome] << "\n" << endl;

            cout << "[1] Original Tic-Tac-Toe" << endl;
            cout << "[2] Battle Tic-Tac-Toe" << endl;
            cout << "[3] Archetypes Compendium (WIP)" << endl;
            cout << "[4] Show Stats from this Session (WIP)" << endl;
            cout << "[0] Exit" << endl;

            cout << "SELECT Command: ";
            cin >> command;
            break;
        }
        case 2: {
            playBatTicTacToe();
            cout << "I hope that was fun, " << welcomeMessages[randWelcome] << "\n" << endl;

            cout << "[1] Original Tic-Tac-Toe" << endl;
            cout << "[2] Battle Tic-Tac-Toe" << endl;
            cout << "[3] Archetypes Compendium (WIP)" << endl;
            cout << "[4] Show Stats from this Session (WIP)" << endl;
            cout << "[0] Exit" << endl;

            cout << "SELECT Command: ";
            cin >> command;
            break;
        }
        case 3: {
            compendium();
            cout << "How very informative, " << welcomeMessages[randWelcome] << "\n" << endl;

            cout << "[1] Original Tic-Tac-Toe" << endl;
            cout << "[2] Battle Tic-Tac-Toe" << endl;
            cout << "[3] Archetypes Compendium (WIP)" << endl;
            cout << "[4] Show Stats from this Session (WIP)" << endl;
            cout << "[0] Exit" << endl;

            cout << "SELECT Command: ";
            cin >> command;
            break;
        }
        case 4: {
            statsScreen();
            cout << "Now those were some good stats, " << welcomeMessages[randWelcome] << "\n" << endl;

            cout << "[1] Original Tic-Tac-Toe" << endl;
            cout << "[2] Battle Tic-Tac-Toe" << endl;
            cout << "[3] Archetypes Compendium (WIP)" << endl;
            cout << "[4] Show Stats from this Session (WIP)" << endl;
            cout << "[0] Exit" << endl;

            cout << "SELECT Command: ";
            cin >> command;
            break;
        }
        }
    }
}
void MainMenu::playTicTacToe() {
    clearConsole();
    cin.ignore();
    Game* tictactoe = new Game();
    tictactoe->start();
    delete tictactoe;
    clearConsole();
}
void MainMenu::playBatTicTacToe() {
    clearConsole();
    cin.ignore();
    Game* batTicTacToe = new Game();
    batTicTacToe->startBattle();
    delete batTicTacToe;
    clearConsole();
}
void MainMenu::compendium() {
    cout << "\n\n\nOh, I have so many ideas for this one, just you wait\n\n\n";
    clearConsole();
}
void MainMenu::statsScreen() {
    cout << "\n\n\nOh, I have so many ideas for this one, just you wait\n\n\n";
    clearConsole();
}
void MainMenu::clearConsole() {
    system("cls");
}
void MainMenu::randWelcomer() {
    int length = sizeof(welcomeMessages) / sizeof(welcomeMessages[0]);
    srand(static_cast<unsigned int>(std::time(nullptr)));
    randWelcome = rand() % length;
}

#pragma endregion
// main 
int main()
{
    MainMenu *menu = new MainMenu();

    menu->startTheProgram();

}