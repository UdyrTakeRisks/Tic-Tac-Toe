
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

//Tic Tac Toe Game

void createMenu(){
    cout<<endl<<"\t\tWELCOME TO THE TIC TAC TOE GAME"<<endl;
    cout<<"1- Play the Game "<<endl;
    cout<<"2- Show the Winners "<<endl;
    cout<<"3- Show the Losers "<<endl;
    cout<<"4- Exit "<<endl;
}

void generateBoard(const vector<char>& board){

    cout<<"     POSITIONS         "<<endl
        <<"        1|2|3          "<<endl
        <<"        4|5|6          "<<endl
        <<"        7|8|9          "<<endl
        <<"                       "<<endl
        <<"      |        |       "<<endl
        <<" "<<board[0]<<"    |   " <<board[1]<<"    |   " << board[2] <<endl
        <<"      |        |       "<<endl
        <<"-----------------------"<<endl
        <<"      |        |       "<<endl
        <<" "<<board[3]<<"    |   " <<board[4]<<"    |   " << board[5] <<endl
        <<"      |        |       "<<endl
        <<"-----------------------"<<endl
        <<"      |        |       "<<endl
        <<" "<<board[6]<<"    |   " <<board[7]<<"    |   " << board[8] <<endl
        <<"      |        |       "<<endl
        <<"                       "<<endl;
}

bool checkWin(const vector<char>& board, char symbol){
    for(int i=0;i<board.size();i+=3) {
        //check rows (horizontal)
        if (board[i] == symbol && board[i+1] == symbol && board[i+2] == symbol)
            return true;
    }
    for(int i=0;i<board.size();i++){
        //check columns (vertical)
        if(board[i] == symbol && board[i+3] == symbol && board[i+6] == symbol)
            return true;
    }
    int i=0;
    //check diagonals
    //right diagonal
    if(board[i] == symbol && board[i+4] == symbol && board[i+8] == symbol)
        return true;
    //left diagonal
    if(board[i+2] == symbol && board[i+4] == symbol && board[i+6] == symbol)
        return true;

    return false;
}

bool checkTie(const vector<char>& board){
    for(char tile : board){
        //check if there is an empty tile
        if(tile == ' ')
            return false;
    }
    //if no empty tile and no winner then it's a draw
    return true;
}

void makeMove(vector<char>& board, int position, char symbol){
    board[position] = symbol;
}

void takePlayerDetails(string& player1Name, string& player2Name, char& player1Symbol, char& player2Symbol){

    int player1Choice;
    cout<<"Player1, Enter your name: ";
    cin>>player1Name;
    while(true) {
        cout<<"Choose your symbol [1 or 2]:  1. X  2. O : ";
        cin>>player1Choice;
        if(player1Choice == 1) {
            player1Symbol = 'X';
            player2Symbol = 'O';
            break;
        }
        if(player1Choice == 2) {
            player1Symbol = 'O';
            player2Symbol = 'X';
            break;
        }else{
            cout << "\nInvalid Choice, please try again.\n" << endl;
            continue;
        }
    }
    cout<<"Player2, Enter your name: ";
    cin>>player2Name;
}

void writeToFile(string& winnerName, string& loserName){
    //write to file and end
    ofstream winnerFile;
    winnerFile.open("Winners.txt",ofstream::app);
    
    winnerFile<<"- " <<winnerName<<endl;
    winnerFile.close();

    ofstream loserFile;
    loserFile.open("Losers.txt",ofstream::app);

    loserFile<<"- " <<loserName<<endl;
    loserFile.close();
}
void readWinnerFile(){
    ifstream winnerFile("Winners.txt");
    if(!winnerFile.good()) //if file is still not created
        cout<<"No Winners Yet!"<<endl;
    else {
        string winners;
        int i = 1;
        while (getline(winnerFile, winners)) {
            cout << i << winners << endl;
            i++;
        }
    }
}
void readLoserFile(){
    ifstream loserFile("Losers.txt");
    if(!loserFile.good()) //if file is still not created
        cout<<"No Losers Yet!"<<endl;
    else {
        string losers;
        int i = 1;
        while (getline(loserFile, losers)) {
            cout << i << losers << endl;
            i++;
        }
    }
}

bool checkInvalidMove(vector<char>& board, int position){
    if(position < 0 || position > 9 || board[position] != ' ') {
        cout << "Invalid move, Please choose another tile\n" << endl;
        return true;
    }
    return false;
}

void playGame(){
    vector<char> board(9,' '); // Initialization with empty tiles
    string player1Name, player2Name;
    char player1Symbol = ' ', player2Symbol = ' ';
    int position;
    bool P1winnerFlag = false, P2winnerFlag = false;
    takePlayerDetails(player1Name,player2Name,player1Symbol,player2Symbol);

    while(true) {
        generateBoard(board);

        cout<<player1Name<<"("<<player1Symbol<<")"<<", Choose your move from positions [1-9]: ";
        cin>>position;
        cout<<endl;
        // the index is zero-based
        position--;
        if(checkInvalidMove(board,position))
            continue;
        makeMove(board,position,player1Symbol);

        //check player1 winning
        if(checkWin(board,player1Symbol)){
            generateBoard(board);
            cout<<player1Name<<" Wins!"<<endl;
            P1winnerFlag = true;
            break;
        }

        //check draw/tie after player1 last move
        if(checkTie(board)){
            generateBoard(board);
            cout<<"Tie!"<<endl;
            break;
        }

        generateBoard(board);

        while(true) {
            cout<<player2Name<<"("<<player2Symbol<<")"<<", Choose your move from positions [1-9]: ";
            cin >> position;
            cout<<endl;
            // the index is zero-based
            position--;
            if (checkInvalidMove(board, position)) {
                generateBoard(board);
                continue;
            }
            else
                break;
        }
        makeMove(board,position,player2Symbol);

        //check player2 winning
        if(checkWin(board,player2Symbol)){
            generateBoard(board);
            cout<<player2Name<<" Wins!"<<endl;
            P2winnerFlag = true;
            break;
        }

    }
    // check for the winner/loser players
    if(P1winnerFlag == true)
        writeToFile(player1Name,player2Name);
    if(P2winnerFlag == true)
        writeToFile(player2Name,player1Name);
}


int main() {

    int menuChoice;
    while(true){
        createMenu();
        cout<<"Choice: ";
        cin>>menuChoice;
        switch (menuChoice) {
            case 1:
                playGame();
                break;
            case 2:
                readWinnerFile();
                break;
            case 3:
                readLoserFile();
                break;
            case 4:
                cout<<"\nThanks for playing.\n";
                exit(0);
            default:
                cout<<"You entered invalid number, please try again"<<endl;
        }
    }
}
