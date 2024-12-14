#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include <windows.h>
#include <fstream>

using namespace std;

#pragma region Rules Class
class Rules
{
public:
    Rules();
    bool verifyInput(string);
    bool isDone();
    bool checkCorrectCharacterBattle(string);
    bool paladinRules(string, string);
    bool alchemistRules(string);
    int getGamesPlayed();
    int getP1Wins();
    int getP2Wins();
    int getTies();
private:
    string mockBoard[9] = { "1","2","3","4","5","6","7","8","9" };
    string allowedBattleTokens[59]{ "?","!","*","~","$","%","#","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z" };
    int mockTurnCounter = 0;
    int winningCombos[9][3];
    string XorO;
    int gamesPlayed = 0;
    int p1Wins = 0;
    int p2Wins = 0;
    int ties = 0;
    bool isInRange(int);
    bool isInteger(const string&);
    bool isAvailble(int);
    bool threeInARow(int, int, int);
    bool isAdjadcent(int, int);
    bool isTaken(int);
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
bool Rules::verifyInput(string space) {
    bool correctSpace = true;
    int mark;

    if (isInteger(space)) {
        mark = stoi(space);
        correctSpace = isInRange(mark);
        correctSpace = isAvailble(mark);
    }
    else {
        correctSpace = false;
    }

    return correctSpace;
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
            gamesPlayed++;
            if (XorO == "X") {
                p1Wins++;
            } else {
                p2Wins++;
            }
            return true;
        }
    }

    for (int i = 0; i <= 8; i++) {
        if (isInteger(mockBoard[i]))
            return false;
    }

    cout << "Game is over, it's a tie, womp womp\nPress [Enter] to continue";
    gamesPlayed++;
    ties++;
    return true;
}
bool Rules::threeInARow(int indexOne, int indexTwo, int indexThree) {
    return mockBoard[indexOne] == mockBoard[indexTwo] && mockBoard[indexTwo] == mockBoard[indexThree];
}
bool Rules::checkCorrectCharacterBattle(string token) {
    bool isAllGood = false;
    int allowedTokensSize = sizeof(allowedBattleTokens) / sizeof(allowedBattleTokens[0]);

    for (int i = 0; i < allowedTokensSize; i++) {
        if (token == allowedBattleTokens[i])
            isAllGood = true;
    }

    return isAllGood;
}
bool Rules::paladinRules(string firstPos, string secondPos) {
    if (mockTurnCounter % 2 == 0)
        XorO = "X";
    else
        XorO = "O";
    if (!isInteger(firstPos))
        return false;
    if (!isInteger(secondPos))
        return false;
    if (!isAdjadcent(stoi(firstPos), stoi(secondPos)))
        return false;
    if (!(mockBoard[stoi(firstPos)-1] == XorO))
        return false;
    if (!isAvailble(stoi(secondPos)))
        return false;
    mockBoard[stoi(firstPos) - 1] = " ";
    return true;
}
bool Rules::isAdjadcent(int firstPos, int secondPos) {
    if ((firstPos == 6 && secondPos == 7) || (firstPos == 7 && secondPos == 6))
        return false;
    if ((firstPos == 3 && secondPos == 4) || (firstPos == 4 && secondPos == 3))
        return false;
    if ((firstPos + 3 == secondPos) || (firstPos + 1 == secondPos) || (firstPos - 1 == secondPos) || (firstPos - 3 == secondPos))
        return true;
    return false;
}
bool Rules::alchemistRules(string tile) {
    if (!isInteger(tile))
        return false;
    int intTile = stoi(tile) - 1;
    if (!isInRange(intTile))
        return false;
    if (!(mockBoard[intTile] == "O" || mockBoard[intTile] == "X"))
        return false;
    return true;
}
int Rules::getGamesPlayed() { return gamesPlayed; }
int Rules::getP1Wins() { return p1Wins; }
int Rules::getP2Wins() { return p2Wins; }
int Rules::getTies() { return ties; }

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
    int getGamesPlayed();
    int getP1Wins();
    int getP2Wins();
    int getTies();
private:
    int gamesPlayed = 0;
    int p1Wins = 0;
    int p2Wins = 0;
    int ties = 0;
    int playerPlay(Rules*, string);
    void useSpecialMove(Rules*, Board*, string, string);
    void transferStats(int, int, int, int);
};

Game::Game() {}
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
            transferStats(rules->getGamesPlayed(), rules->getP1Wins(), rules->getP2Wins(), rules->getTies());
            delete rules;
            continue;
        }

        cout << "now it's player two\n";
        mark = playerPlay(rules, "O");

        board->markBoard(mark, "O");
        board->printBoard();

        if (rules->isDone()) {
            gameInPlay = false;
            transferStats(rules->getGamesPlayed(), rules->getP1Wins(), rules->getP2Wins(), rules->getTies());
            delete rules;
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

        if (rules->verifyInput(input)) {
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
void Game::startBattle() {
    Board* board = new Board();
    Rules* rules = new Rules();
    string p1Token, p2Token, p1Class, p2Class, input;
    int mark;
    bool gameInPlay = true;
    bool canContinue;

#pragma region starting stuff
    cout << "(The vaild tokens are as follows: A – Z, a – z, ?, !, *, ~, $, %, and #)\nPlayer One, please type what character yuo want to use:\n";
    getline(cin, input);
    while (!rules->checkCorrectCharacterBattle(input)) {
        cout << "\nNot quite, Remember the valid ones are: A – Z, a – z, ?, !, *, ~, $, %, and #, try again:\n";
        getline(cin, input);
    }
    p1Token = input;
    cout << "\nAlright, now Player Two, type yours:\n";
    getline(cin, input);
    while (!rules->checkCorrectCharacterBattle(input)) {
        cout << "\nNot quite, Remember the valid ones are: A – Z, a – z, ?, !, *, ~, $, %, and #, try again:\n";
        getline(cin, input);
    }
    p2Token = input;

    cout << "\nPlayer One, please type which class you will be (P for Paladin or A for Alchemist):\n";
    getline(cin, input);
    while (input == "p" || input == "a") {
        cout << "\nNot quite, Remember it's P for Paladin or A for Alchemist, try again:\n";
        getline(cin, input);
    }
    p1Class = input;
    cout << "\nAlright, now Player Two, type yours:\n";
    getline(cin, input);
    while (input == "p" || input == "a") {
        cout << "\nNot quite, Remember it's P for Paladin or A for Alchemist, try again:\n";
        getline(cin, input);
    }
    p2Class = input;
#pragma endregion starting stuff

    while (gameInPlay) {
        board->printBoard();

        cout << "let's do this thing!\n";
        canContinue = false;

        while (!canContinue) {
            cout << "make your move or use your ability by pressing 'C'\n";
            getline(cin, input);

            if (input == "c" || input == "C") {
                useSpecialMove(rules, board, p1Token ,p1Class);
                canContinue = true;
            } else if (rules->verifyInput(input)) {
                mark = stoi(input);
                cout << "\n";
                board->markBoard(mark, p1Token);
                canContinue = true;
            } else {
                cout << "\nnot quite try again\n";
            }
        }
        
        board->printBoard();
        if (rules->isDone()) {
            gameInPlay = false;
            transferStats(rules->getGamesPlayed(), rules->getP1Wins(), rules->getP2Wins(), rules->getTies());
            delete rules;
            continue;
        }

        canContinue = false;
        cout << "now it's player two\n";
        while (!canContinue) {
            cout << "make your move or use your ability by pressing 'C'\n";
            getline(cin, input);

            if (input == "c" || input == "C") {
                useSpecialMove(rules, board, p2Token, p2Class);
                canContinue = true;
            } else if (rules->verifyInput(input)) {
                mark = stoi(input);
                cout << "\n";
                board->markBoard(mark, p2Token);
                canContinue = true;
            } else {
                cout << "\nnot quite try again\n";
            }
        }

        board->printBoard();

        if (rules->isDone()) {
            gameInPlay = false;
            transferStats(rules->getGamesPlayed(), rules->getP1Wins(), rules->getP2Wins(), rules->getTies());
            delete rules;
            continue;
        }
    }
    string nothing;
    getline(cin, nothing);
}
void Game::useSpecialMove(Rules* rules, Board* board, string playerToken, string playerClass) {
    bool canContinue = false;
    string firstPos, secondPos, transTile;
    if (playerClass == "P") {
        while (!canContinue) {
            cout << "\nWhich do you want to move? or press 'b' to go back (warning it will skip your turn)\n";
            getline(cin, firstPos);
            if (firstPos == "B" || firstPos == "b"){
                canContinue = true;
                break;
            }
            cout << "\nAnd where do you want to move it?\n";
            getline(cin, secondPos);
            if (rules->paladinRules(firstPos, secondPos)) {
                board->markBoard(stoi(secondPos), playerToken);
                board->markBoard(stoi(firstPos), firstPos);
                canContinue = true;
            } else {
                cout << "\none or more of your responses were incorrect, please try again\n";
            }
        }
    } else if (playerClass == "A"){
        while (!canContinue) {
            cout << "\nWhich tile do you want to transmute? or press 'b' to go back (warning it will skip your turn)\n";
            getline(cin, transTile);
            if (transTile == "B" || transTile == "b") {
                canContinue = true;
                break;
            }
            if (rules->alchemistRules(transTile)) {
                board->markBoard(stoi(transTile), playerToken);
                canContinue = true;
            } else {
                cout << "\nThat is an invalid tile\n";
            }
        }
    }
}
void Game::transferStats(int Games, int p1, int p2, int ties) {
    gamesPlayed += Games;
    p1Wins += p1;
    p2Wins += p2;
    this->ties += ties;
}
int Game::getGamesPlayed() { return gamesPlayed; }
int Game::getP1Wins() { return p1Wins; }
int Game::getP2Wins() { return p2Wins; }
int Game::getTies() { return ties; }

#pragma endregion

class StatsTracker {
public:
    StatsTracker();
    StatsTracker(int, int, int, int);
    void dispInfo();
private:
    void printToFile();
    int gamesPlayed = 0;
    int p1Wins = 0;
    int p2Wins = 0;
    int ties = 0;
};

StatsTracker::StatsTracker() {}
StatsTracker::StatsTracker(int games, int p1Win, int p2Win, int ties) {
    gamesPlayed = games;
    p1Wins = p1Win;
    p2Wins = p2Win;
    this->ties = ties;
}
void StatsTracker::dispInfo() {
    int command;
    bool inProgress = true;

    cout << "+--------------------------------------+" << "\n";
    cout << "+             Stats Screen             +" << "\n";
    cout << "+--------------------------------------+" << "\n\n";

    cout << "Here are your awesome statistics for this session!\n" << endl;

    cout << "Games played: " << gamesPlayed << endl;
    cout << "Times player 1 won: " << p1Wins << endl;
    cout << "Times player 2 won: " << p2Wins << endl;
    cout << "Times drew: " << ties << endl << endl;

    while (inProgress) {
        cout << "[1] Print to file" << endl;
        cout << "[0] Exit" << endl;
        cout << "SELECT Command: ";
        cin >> command;

        switch (command) {
        case 0: {
            inProgress = false;
            cout << "And back to the menu you go!" << endl;
            break;
        }
        case 1: {
            printToFile();
            break;
        }
        default: {
            cout << "Invalid input! Please enter 0 or 1." << endl;
            break;
        }
        }
    }
}

void StatsTracker::printToFile() {
    string fileName = "Stats.txt";
    ofstream outFile;

    outFile.open(fileName);

    if (outFile.is_open()) {
        outFile << "+--------------------------------------+" << "\n";
        outFile << "+             Stats Screen             +" << "\n";
        outFile << "+--------------------------------------+" << "\n\n";

        outFile << "Here are your awesome statistics for this session!\n" << endl;

        outFile << "Games played: " << gamesPlayed << endl;
        outFile << "Times player 1 won: " << p1Wins << endl;
        outFile << "Times player 2 won: " << p2Wins << endl;
        outFile << "Times drew: " << ties << endl << endl;

        outFile.close();

        cout << "File \"" << fileName << "\" has been created and written successfully!" << endl;
    }
    else {
        cerr << "Error: Could not open the file for writing!" << endl;
    }
}

#pragma region Menu Class

class MainMenu {
public:
    MainMenu();
    void startTheProgram();
private:
    string welcomeMessages[3] = { "welcome back to the menu", "aaand we're back", "here we are again" };
    int randWelcome;
    int gamesPlayed = 0;
    int p1Wins = 0;
    int p2Wins = 0;
    int ties = 0;
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
    gamesPlayed += tictactoe->getGamesPlayed();
    p1Wins += tictactoe->getP1Wins();
    p2Wins += tictactoe->getP2Wins();
    ties += tictactoe->getTies();
    delete tictactoe;
    clearConsole();
}
void MainMenu::playBatTicTacToe() {
    clearConsole();
    cin.ignore();
    Game* batTicTacToe = new Game();
    batTicTacToe->startBattle();
    gamesPlayed += batTicTacToe->getGamesPlayed();
    p1Wins += batTicTacToe->getP1Wins();
    p2Wins += batTicTacToe->getP2Wins();
    ties += batTicTacToe->getTies();
    delete batTicTacToe;
    clearConsole();
}
void MainMenu::compendium() {
    cout << "Oh I have so many Ideas for this one\n";
    clearConsole();
}
void MainMenu::statsScreen() {
    clearConsole();
    cin.ignore();
    StatsTracker* stats = new StatsTracker(gamesPlayed, p1Wins, p2Wins, ties);
    stats->dispInfo();
    delete stats;
    clearConsole();
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