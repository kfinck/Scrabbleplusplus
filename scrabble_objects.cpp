#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
// #include <bits/stdc++.h>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <utility>
#include <map>
#include "wordChecker.h"
#include <sstream>

using namespace std;





class Tile
{
private:

public:
    char letter;
    int value;

};




class Board: public Tile
{
private:
    int placeValue;
    Tile board[15][15];
    map<char, int> letter_values = {
            {'A', 1}, {'B', 3}, {'C', 3}, {'D', 2}, {'E', 1}, {'F', 4}, {'G', 2},
            {'H', 4}, {'I', 1}, {'J', 8}, {'K', 5}, {'L', 1}, {'M', 3}, {'N', 1},
            {'O', 1}, {'P', 3}, {'Q', 10},{'R', 1}, {'S', 1}, {'T', 1}, {'U', 1},
            {'V', 4}, {'W', 4}, {'X', 8}, {'Y', 4}, {'Z', 10}, {'_', 0}
    };
    Trie wordChecker;
public:
    char letter;
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    vector<pair<int, int>> doubleLetterScore = { {0, 3}, {0, 11}, {2,6}, {2,8},{3,0},{3,7},{3,14},{6,2},{6,6},{6,8},{6,12},{7,3},{7,11},{8,2},{8,6},{8,8},{8,12},{11,0},{11,7},{11,14},{12,6},{12,8},{14,3},{14,11} };
    vector<pair<int, int>> tripleLetterScore = { {1,5},{1,9},{5,1},{5,5},{5,9},{5,13},{9,1},{9,1},{9,5},{9,9},{9,13},{13,5},{13,9} };
    vector<pair<int, int>> doubleWordScore = { {1,1},{2,2},{3,3},{4,4},{1,13},{2,12},{3,11},{4,10},{13,1},{12,2},{11,3},{10,4},{13,13},{12,12},{11,11},{10,10} };
    vector<pair<int, int>> tripleWordScore = { {0,0},{0,7},{0,14},{7,0},{7,14},{14,0},{14,7},{14,14} };
    Board()
    {
        //board.resize(15, vector<char>(15, ' '));

        initializeTiles();
    }

    Board(string path){
      wordChecker.addFile(path);
      initializeTiles();
    }

    void initializeTiles()
    {
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
                if (find(doubleLetterScore.begin(), doubleLetterScore.end(), make_pair(i, j)) != doubleLetterScore.end())
                {
                    board[i][j].value = 1;
                    board[i][j].letter = ' ';
                }
                else if (find(tripleLetterScore.begin(), tripleLetterScore.end(), make_pair(i, j)) != tripleLetterScore.end())
                {
                    board[i][j].value = 2;
                    board[i][j].letter = ' ';
                }
                else if (find(doubleWordScore.begin(), doubleWordScore.end(), make_pair(i, j)) != doubleWordScore.end())
                {
                    board[i][j].value = 3;
                    board[i][j].letter = ' ';
                }
                else if (find(tripleWordScore.begin(), tripleWordScore.end(), make_pair(i, j)) != tripleWordScore.end())
                {
                    board[i][j].value = 4;
                    board[i][j].letter = ' ';
                }
                else {
                    board[i][j].value = 15;
                    board[i][j].letter = ' ';
                }
        }
    }

    void displayBoard()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                int k = board[i][j].value;
                if (board[i][j].letter == ' ') {
                    SetConsoleTextAttribute(hconsole, k);
                    cout << "0" << " ";
                }
                else {
                    SetConsoleTextAttribute(hconsole, k);
                    cout << board[i][j].letter << " ";
                }

                //cout << i << "," << j << " ";
            }
            cout << endl;
        }

    }
    int getWordScore(const string& word, const vector<int>& letter_multipliers, const int& word_multiplier) {
        int score = 0;

        for (size_t i = 0; i < word.size(); i++) {
            score += letter_values[word[i]] * letter_multipliers[i];
        }

        return score * word_multiplier;
    }

    void placeTile(int row, int col, char letter)
    {
        board[row][col].letter = letter;

    }

    bool CheckBoard(){
      //iterates through board - checking if consecutive letters are words!!
      //checks horizontally - then vertically
      //floating letters not checked here - they will be checked when moves are made.
      //cout << "at the beginning :))" << endl;
      string word = "";
      for(int i = 0; i < 15; i++){
        for(int j = 0; j< 15; j++){
          if(board[i][j].letter != ' '){ //check if spot has a tile on it
            word.push_back(board[i][j].letter);
            if(j == 14 && word.length() > 1){ //word goes to end of row/column
               
              bool result = wordChecker.contains(word);
              if(result){
                cout << word << " is a word!" << endl;
                word = ""; //remove valid word
              }
              else{
                cout << word << " is NOT a word!" << endl;
                return false; //invalid word found -- STOP
              }
            }
          }
          else if(word.length() > 1){ //Word ended and is more than 1 letter - check
            //cout << word << endl; 
            bool result = wordChecker.contains(word);
            if(result){
              cout << word << " is a word!" << endl;
              word = ""; //remove valid word
            }
            else{
              cout << word << " is NOT a word!" << endl;
              return false; //invalid word found -- STOP
            }
          }
          else{ //word is just one letter
            word = ""; //single letter - ignore (for now)
          }
        }
      }
      //column by column
      word = "";
      for(int i = 0; i < 15; i++){
        for(int j = 0; j< 15; j++){
          if(board[j][i].letter != ' '){ //check if spot has a tile on it
            word.push_back(board[j][i].letter);
            if(i == 14 && word.length() > 1){ //word goes to end of row/column
              //cout << word << endl; 
              bool result = wordChecker.contains(word);
              if(result){
                cout << word << " is a word!" << endl;
                word = ""; //remove valid word
              }
              else{
                cout << word << " is NOT a word!" << endl;
                return false; //invalid word found -- STOP
              }
            }
          }else if(word.length() > 1){ //Word ended and is more than 1 letter - check
            cout << word << endl;
            bool result = wordChecker.contains(word);
            if(result){
              cout << word << " is a word!" << endl;
              word = ""; //remove valid word
            }
            else{
              cout << word << " is NOT a word!" << endl;
              return false; //invalid word found -- STOP
            }
          }
          else{
            word = ""; //single letter - ignore (for now)
          }
        }
      }
      //cout << "at the end :))" << endl;
      return true; //made it to end -- all good
    }

    bool checkMove(vector<pair<int, int>> coords, bool firstMove){
    //must check if move is valid
    //first move must go thru center square
    //other moves must connect to another word
    pair<int,int> center = {7,7};
    if(firstMove){ //after first move - must be connected 
      for (const auto& p : coords) {
        cout << p.first << ": " << p.second << endl;
        if( p.first == 0 && p.second == 0){ //top left (0,0)
          if(board[p.first+1][p.second].letter != ' '){
            return true;
          }
          
          else if(board[p.first][p.second+1].letter != ' '){
            return true;
          }
        }
        else if( p.first == 14 && p.second == 0){ //top right (14,0)
          if(board[p.first-1][p.second].letter != ' '){
            return true;
          }
          else if(board[p.first][p.second+1].letter != ' '){
            return true;
          }
        }
        else if(p.first == 0 && p.second == 14){ //bottom left (0,14)
          
          if(board[p.first+1][p.second].letter != ' '){
            return true;
          }
          else if(board[p.first][p.second-1].letter != ' '){
            return true;
          }
        }
        else if(p.first == 14 && p.second == 14){ //bottom right (14,14)
          
          if(board[p.first-1][p.second].letter != ' '){
            return true;
          }
          else if(board[p.first][p.second-1].letter != ' '){
            return true;
          }
        }
        else if(p.first == 14){ //right side
          if(board[p.first-1][p.second].letter != ' '){
            return true;
          }
          else if(board[p.first][p.second+1].letter != ' '){
            return true;
          }
          else if(board[p.first][p.second-1].letter != ' '){
            return true;
          }
        }
        else if(p.first == 0){ //left side
          if(board[p.first+1][p.second].letter != ' '){
            return true;
          }
          else if(board[p.first][p.second+1].letter != ' '){
            return true;
          }
          else if(board[p.first][p.second-1].letter != ' '){
            return true;
          }
        }
        else if(p.second == 14){ //bottom
          if(board[p.first+1][p.second].letter != ' '){
            return true;
          }
          else if(board[p.first-1][p.second].letter != ' '){
            return true;
          }
          else if(board[p.first][p.second-1].letter != ' '){
            return true;
          }
        }
        else if(p.second == 0){ //top
          if(board[p.first+1][p.second].letter != ' '){
            return true;
          }
          else if(board[p.first-1][p.second].letter != ' '){
            return true;
          }
          else if(board[p.first][p.second+1].letter != ' '){
            return true;
          }
        }
        else{ //middle tiles
          if(board[p.first+1][p.second].letter != ' '){
            return true;
          }
          else if(board[p.first-1][p.second].letter != ' '){
            return true;
          }
          else if(board[p.first][p.second+1].letter != ' '){
            return true;
          }
          else if(board[p.first][p.second-1].letter != ' '){
            return true;
          }
        }
      }
      return false;
    }
    else{ //first move - must go thru middle
      if( find(coords.begin(), coords.end(), center) != coords.end() ){
        firstMove = true;
        return true;
      }
      else{
        cout << "First move must go through the middle tile!" << endl;
        return false;
      }
    }
  }

};


//added 4/23/2023
class bag
{
private:
    std::vector<char> tiles;
public:
    bag() {
        map<char, int> tile_distribution = {
                {'A', 9},
                {'B', 2},
                {'C', 2},
                {'D', 4},
                {'E', 12},
                {'F', 2},
                {'G', 3},
                {'H', 2},
                {'I', 9},
                {'J', 1},
                {'K', 1},
                {'L', 4},
                {'M', 2},
                {'N', 6},
                {'O', 8},
                {'P', 2},
                {'Q', 1},
                {'R', 6},
                {'S', 4},
                {'T', 6},
                {'U', 4},
                {'V', 2},
                {'W', 2},
                {'X', 1},
                {'Y', 2},
                {'Z', 1},
                {'_', 2}
        };
        for (auto& tile : tile_distribution) {
            for (int i = 0; i < tile.second; ++i) {
                tiles.push_back(tile.first);
            }
        }


        srand(time(0));
        random_shuffle(tiles.begin(), tiles.end());
    }

    char draw_tile() {
        if (tiles.empty()) {
            throw runtime_error("Tile bag is empty.");
        }
        char tile = tiles.back();
        tiles.pop_back();
        return tile;
    }
    void return_tile(char tile)
    {
      tiles.push_back(tile);
    }

    bool is_empty() {
        return tiles.empty();
    }

    int remaining_tiles() {
        return tiles.size();
    }

    void end_tiles() {
        int n = tiles.size();
        for (int i = n - 4; i < n; i++) {
            cout << tiles[i] << " ";
        }
        cout << "\n";
    }
  void shuffle_bag() {
        srand(time(0));
        random_shuffle(tiles.begin(), tiles.end());
    }
};

class player {
private:
    string name;
    int score;
    vector<char> rack;
    int racksize;
public:
    player(const string& player_name, bag& tile_bag) {
        name = player_name;
        score = 0;
        racksize = 7;
        for (int i = 0; i < racksize; i++) {
            add_tile(tile_bag);
        }
    }


    // use bag draw_tile() method to pop / push tile into player rack object
    void add_tile(bag& tile_bag) {
        char tile = tile_bag.draw_tile();
        //cout << "Player " << name << " received the letter " << tile << endl;
        rack.push_back(tile);
    }

    bool has_tile(char c){
      if (find(rack.begin(), rack.end(), c) != rack.end()) {
        return true;
      }
      else {
        return false;
      }
    }

    void print_rack() const {
        cout << this->name << "'s rack: ";
        for (char tile : rack) {
            std::cout << tile << "/";
        }
        cout << "\n";
    }

    void add_score(int points) {
        score += points;
    }

    void print_score() {
        cout << score << endl;
    }

    void print_name() {
        cout << name << endl;
    }

    vector<char> get_rack() const {
        return rack;
    }


    int get_score() {
        return score;
    }

    string get_name() {
        return name;
    }

    void set_rack(vector<char> newRack){
      rack = newRack;
    }
};


class Game{
  private:
    bool firstMove = false;
    vector<player> players;
    int num_players;
    Board board;
    bag scrabbleBag;
    int turnLimit;
  public:
  Game(vector<player> players_list, int num, Board b,bag sb, int turns){
    players = players_list;
    num_players = num;
    board = b;
    scrabbleBag = sb;
    turnLimit = turns;
    Game_loop(0,0);
  }

  

  void Game_loop(int player_num,int turn){
    player current = players[player_num]; //get current player
    cout << current.get_name() << "'s turn!" <<  endl;
    cout << "Score: " << current.get_score() << endl;
    //current.print_rack();
    Board tempBoard = board; //allows us to attempt moves without editing the real board
    vector<char> tempRack = current.get_rack();
    
    vector<pair<int, int>> coords; 
    while(true){ //player turn runs untill they end their turn - either drawing or making a move
      tempBoard.displayBoard();

      cout << current.get_name() << "'s rack: ";
      for (char tile : tempRack) {
          std::cout << tile << "/";
      }
      cout << "\n";
      cout << "Draw - /draw" << endl;

      cout << "exchange - /exchange (number of letters to replace)" << endl; //LJ

      cout << "to place a tile - /place (x) (y) (letter)" << endl;
      cout << "to undo - /undo" << endl;
      cout << "to confirm moves & end turn - /end" << endl;
      string input;
      getline(cin,input); //idk why this works better than cin >> lmao
      if(input.find("/exchange") != string::npos){ //draws tile then ends turn -- need to add case when bag is empty?
        istringstream ss(input); //get args
        string input;
        getline(ss, input, ' ');
        getline(ss, input, ' ');// this line overwrites "input" from "/exchange" to the "number of letters to replace"
        int input = stoi(intput);
        <vector> char discardedTiles;
        for(int i = 0;i < input; i++)
        {
          string c;
          cout << "Input letter to discard" << endl;
          getline(cin, c);
          if (find(tempRack.begin(), tempRack.end(), c) != tempRack.end()) {
          //delete tile from temporary rack
          auto it = find(tempRack.begin(), tempRack.end(), c[0]);
        if (it != tempRack.end()) {
            discardedTiles.push_back(c[0]);
            tempRack.erase(it);
        }

    }
        }
        for(int i = 0; i < input; i++)
        {
          current.add_tile(scrabbleBag);
        }
        for(int i = 0; i < discardedTiles.size(); i++)
        {
          scrabbleBag.return_tile(discardedTiles[i]);
          
        }
        discardedTiles.clear();
        scrabbleBag.shuffle_bag();
        //LJ
        break;
      
      else if(input.find("/place") != string::npos){ //place tiles one by one
        istringstream ss(input); //get args
        string x_s, y_s, c_s;
        getline(ss, x_s, ' ');
        getline(ss, x_s, ' ');
        getline(ss, y_s, ' ');
        getline(ss, c_s, ' ');
        cout << x_s << y_s << c_s << endl;
        int x = stoi(x_s);
        int y = stoi(y_s);
        char c = c_s[0];
        auto it = find(tempRack.begin(), tempRack.end(), c);
        if (it != tempRack.end()) {
          //delete tile from temporary rack
          tempRack.erase(it);
          tempBoard.placeTile(x,y,c);
          coords.emplace_back(x,y);
        }
        else{
          cout << "Only use tiles from your rack!!" << endl;
        }
        
      }
      else if(input.find("/undo") != string::npos){ //undo all tiles placed this turn;
        tempBoard = board; //revert to original board
        tempRack = current.get_rack();
        coords.clear();
      }
      else if(input.find("/end") != string::npos){ //check if placed tiles are valid
        //still need to check if tiles being played are in the player's rack & removing them from the rack once played
        //also must calculate score of turn
        if(tempBoard.CheckBoard() && board.checkMove(coords,firstMove)){ 
          board = tempBoard;
          cout << "Good move!" << endl;
          current.set_rack(tempRack);
          firstMove = true;
          break;
        }
        else{
          tempBoard = board;
          tempRack = current.get_rack();
          cout << "Invalid move!" << endl;
          coords.clear();
        }
      }
      else{
        cout << "please enter a valid input" << endl;
      }

    }
    if(player_num == num_players - 1){ //either end game, go to next player, or loop back to first player
      if(turn == turnLimit){
        endGame();
      }
      else{
        Game_loop(0,turn+1);
      }
    }
    else{
      Game_loop(player_num+1,turn);
    }
  }

  void endGame(){
    player winner = players[0];
    cout << "GAME OVER" << endl;
    for(int i = 0; i < num_players; i++){ //print players and find winner - need edge case for ties
      cout << players[i].get_name() << " : " << players[i].get_score() << endl; 
      if(players[i].get_score() > winner.get_score()){
        winner = players[i];
      }
    }
    cout << winner.get_name() << " wins!!!" << endl;
  }

};

int main(int argc, char* argv[]) {
    string path = argv[0];
    path.resize(path.length() - 12); //remove exe name from path -- this will have to be changed based on name of executable hehe
    string dPath = path + "ScrabbleDict.txt"; //add dictionary file name
    cout << dPath << endl;
    Board scrabbleBoard(dPath); /// initialize board
    bag scrabbleBag;
    ///start game loop
    int number_of_players = 5;
    while (number_of_players > 4 || number_of_players < 1) {
        cout << " please enter a number of players between 1-4" << endl;
        cin >> number_of_players;
        if (number_of_players > 4) {
            cout << "You cannot have more than four players" << endl;
        }
        if (number_of_players < 1) {
            cout << "You cannot have less than one players" << endl;
        }
    }
    vector<player> players;

    for (int i = 0; i < number_of_players; i++) {


        if (i == 0) {
            string p1name;
            cout << "Player one enter your name" << endl;
            cin >> p1name;
            player p1(p1name, scrabbleBag);
            players.push_back(p1);
        }
        if (i == 1) {
            string p2name;
            cout << "Player two enter your name" << endl;
            cin >> p2name;
            player p2(p2name, scrabbleBag);
            players.push_back(p2);
        }
        if (i == 2) {
            string p3name;
            cout << "Player three enter your name" << endl;
            cin >> p3name;
            player p3(p3name, scrabbleBag);
            players.push_back(p3);
        }
        if (i == 3) {
            string p4name;
            cout << "Player four enter your name" << endl;
            cin >> p4name;
            player p4(p4name, scrabbleBag);
            players.push_back(p4);
        }
    }

    Game g(players,number_of_players,scrabbleBoard,scrabbleBag, 5);

    player Liam("Liam", scrabbleBag);

    scrabbleBoard.placeTile(7, 7, 'S');
    scrabbleBoard.placeTile(7, 8, 'C');
    scrabbleBoard.placeTile(7, 9, 'R');
    scrabbleBoard.placeTile(7, 10, 'A');
    scrabbleBoard.placeTile(7, 11, 'B');
    scrabbleBoard.placeTile(7, 12, 'B');
    scrabbleBoard.placeTile(7, 13, 'L');
    scrabbleBoard.placeTile(7, 14, 'E');

    scrabbleBoard.displayBoard();

    cout << scrabbleBoard.CheckBoard() << endl;

    scrabbleBag.end_tiles();
    Liam.get_rack();
    scrabbleBag.end_tiles();

    std::cout << std::endl;

    return 0;
}