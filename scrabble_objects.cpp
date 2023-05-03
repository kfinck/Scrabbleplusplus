

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

class Board : public Tile
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

  vector<string> words;


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

  Board(string path) {
    wordChecker.addFile(path);
    initializeTiles();
  }
  int getLetterValue(char c)
  {

    return letter_values[c];
  }
  void initializeTiles()
  {
    for (int i = 0; i < 15; i++)
    {
      for (int j = 0; j < 15; j++)
        if (find(doubleLetterScore.begin(), doubleLetterScore.end(), make_pair(i, j)) != doubleLetterScore.end())


        {
          board[i][j].value = 9;
          board[i][j].letter = ' ';
        }
        else if (find(tripleLetterScore.begin(), tripleLetterScore.end(), make_pair(i, j)) != tripleLetterScore.end())
        {

          board[i][j].value = 6;
          board[i][j].letter = ' ';
        }
        else if (find(doubleWordScore.begin(), doubleWordScore.end(), make_pair(i, j)) != doubleWordScore.end())
        {
          board[i][j].value = 10;
          board[i][j].letter = ' ';
        }
        else if (find(tripleWordScore.begin(), tripleWordScore.end(), make_pair(i, j)) != tripleWordScore.end())
        {
          board[i][j].value = 12;
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



  bool placeTile(int row, int col, char letter)
  {
    if (board[row][col].letter == ' ') {
      board[row][col].letter = letter;
      return true;
    }
    else {
      return false;
    }

  }

  int CheckBoard() {


    //iterates through board - checking if consecutive letters are words!!
    //checks horizontally - then vertically
    //floating letters not checked here - they will be checked when moves are made.
    //cout << "at the beginning :))" << endl;


    int score = 0;
    string word = "";
    int wordScore = 0;
    int doubled = 0; //for double word tiles
    int tripled = 0; //for triple word tiles

    for (int i = 0; i < 15; i++) {
      for (int j = 0; j < 15; j++) {
        if (board[i][j].letter != ' ') { //check if spot has a tile on it
          word.push_back(board[i][j].letter);

          pair<int, int> square = { i,j };
          //check for tile multiplier
          if (find(doubleLetterScore.begin(), doubleLetterScore.end(), square) != doubleLetterScore.end()) { //double letter
            wordScore += letter_values[board[i][j].letter] * 2;
          }
          else if (find(tripleLetterScore.begin(), tripleLetterScore.end(), square) != tripleLetterScore.end()) { //triple letter
            wordScore += letter_values[board[i][j].letter] * 3;
          }

          else if (find(doubleWordScore.begin(), doubleWordScore.end(), square) != doubleWordScore.end()) { //double word
            wordScore += letter_values[board[i][j].letter];
            doubled++;
          }

          else if (find(tripleWordScore.begin(), tripleWordScore.end(), square) != tripleWordScore.end()) { //triple word
            wordScore += letter_values[board[i][j].letter];
            tripled++;
          }
          else {
            wordScore += letter_values[board[i][j].letter];
          }
          cout << "letter: " << board[i][j].letter << " value " << wordScore << endl;

          if (j == 14 && word.length() > 1) { //word goes to end of row/column

            bool result = wordChecker.contains(word);
            if (result) {

              if (find(words.begin(), words.end(), word) == words.end()) { //if word is new
                cout << word << " is a word!" << endl;
                words.push_back(word);
                for (int i = 0; i < doubled;i++) {
                  wordScore = wordScore * 2;
                }
                for (int j = 0; j < tripled;j++) {
                  wordScore = wordScore * 3;
                }
                score += wordScore; //only added to score if the word is new
              }
              word = ""; //remove valid word 
              wordScore = 0;
              doubled = 0;
              tripled = 0;
            }
            else {
              cout << word << " is NOT a word!" << endl;
              return 0; //invalid word found -- STOP
            }
          }
        }
        else if (word.length() > 1) { //Word ended and is more than 1 letter - check
          //cout << word << endl; 
          bool result = wordChecker.contains(word);
          if (result) {
            //cout << word << " valid score: " << wordScore << endl;
            if (find(words.begin(), words.end(), word) == words.end()) {
              cout << word << " is a word!" << endl;
              words.push_back(word);
              for (int i = 0; i < doubled;i++) {
                wordScore = wordScore * 2;
              }
              for (int j = 0; j < tripled;j++) {
                wordScore = wordScore * 3;
              }
              score += wordScore;


            }
            word = ""; //remove valid word
            wordScore = 0;
            doubled = 0;
            tripled = 0;
          }


          else {
            cout << word << " is NOT a word!" << endl;
            return 0; //invalid word found -- STOP

          }
        }
        else { //word is just one letter
          word = ""; //single letter - ignore (for now)
          wordScore = 0;

          doubled = 0;
          tripled = 0;

        }
      }
    }
    //column by column
    wordScore = 0;
    word = "";
    for (int i = 0; i < 15; i++) {
      for (int j = 0; j < 15; j++) {
        if (board[j][i].letter != ' ') { //check if spot has a tile on it
          word.push_back(board[j][i].letter);


          pair<int, int> square = { j,i };
          //check for tile multiplier
          if (find(doubleLetterScore.begin(), doubleLetterScore.end(), square) != doubleLetterScore.end()) { //double letter
            wordScore += letter_values[board[j][i].letter] * 2;
          }
          else if (find(tripleLetterScore.begin(), tripleLetterScore.end(), square) != tripleLetterScore.end()) { //triple letter
            wordScore += letter_values[board[j][i].letter] * 3;
          }

          else if (find(doubleWordScore.begin(), doubleWordScore.end(), square) != doubleWordScore.end()) { //double word
            wordScore += letter_values[board[j][i].letter];
            doubled = true;
          }

          else if (find(tripleWordScore.begin(), tripleWordScore.end(), square) != tripleWordScore.end()) { //triple word
            wordScore += letter_values[board[j][i].letter];
            tripled = true;
          }
          else {
            wordScore += letter_values[board[j][i].letter];
          }
          //cout << "letter: " << letter << " value " << value << endl;
          if (i == 14 && word.length() > 1) { //word goes to end of row/column

            bool result = wordChecker.contains(word);
            if (result) {
              if (find(words.begin(), words.end(), word) == words.end()) { //if word is new
                cout << word << " is a word!" << endl;
                words.push_back(word);
                for (int i = 0; i < doubled;i++) {
                  wordScore = wordScore * 2;
                }
                for (int j = 0; j < tripled;j++) {
                  wordScore = wordScore * 3;
                }
                score += wordScore; //only added to score if the word is new
              }
              word = ""; //remove valid word 
              wordScore = 0;
              doubled = 0;
              tripled = 0;


            }
            else {
              cout << word << " is NOT a word!" << endl;
              return 0; //invalid word found -- STOP
            }
          }
        }
        else if (word.length() > 1) { //Word ended and is more than 1 letter - check


          //cout << word << endl; 
          bool result = wordChecker.contains(word);
          if (result) {
            if (find(words.begin(), words.end(), word) == words.end()) {
              cout << word << " is a word!" << endl;
              words.push_back(word);
              for (int i = 0; i < doubled;i++) {
                wordScore = wordScore * 2;
              }
              for (int j = 0; j < tripled;j++) {
                wordScore = wordScore * 3;
              }
              score += wordScore;
            }
            word = ""; //remove valid word
            wordScore = 0;
            doubled = 0;
            tripled = 0;
          }
          else {
            cout << word << " is NOT a word!" << endl;
            return 0; //invalid word found -- STOP
          }
        }
        else { //word is just one letter
          word = ""; //single letter - ignore (for now)
          wordScore = 0;
          doubled = 0;
          tripled = 0;


        }
      }
    }
    //cout << "at the end :))" << endl;

    return score; //made it to end -- all good

  }


  bool checkMove(vector<pair<int, int>> coords, bool firstMove) {
    //must check if move is valid
    //first move must go thru center square
    //other moves must connect to another word
    pair<int, int> center = { 7,7 };
    if (firstMove) { //after first move - must be connected 
      for (const auto& p : coords) {


        //cout << p.first << ": " << p.second << endl;


        if (p.first == 0 && p.second == 0) { //top left (0,0)
          if (board[p.first + 1][p.second].letter != ' ') {
            return true;
          }

          else if (board[p.first][p.second + 1].letter != ' ') {
            return true;
          }
        }
        else if (p.first == 14 && p.second == 0) { //top right (14,0)
          if (board[p.first - 1][p.second].letter != ' ') {
            return true;
          }
          else if (board[p.first][p.second + 1].letter != ' ') {
            return true;
          }
        }
        else if (p.first == 0 && p.second == 14) { //bottom left (0,14)

          if (board[p.first + 1][p.second].letter != ' ') {
            return true;
          }
          else if (board[p.first][p.second - 1].letter != ' ') {
            return true;
          }
        }
        else if (p.first == 14 && p.second == 14) { //bottom right (14,14)

          if (board[p.first - 1][p.second].letter != ' ') {
            return true;
          }
          else if (board[p.first][p.second - 1].letter != ' ') {
            return true;
          }
        }
        else if (p.first == 14) { //right side
          if (board[p.first - 1][p.second].letter != ' ') {
            return true;
          }
          else if (board[p.first][p.second + 1].letter != ' ') {
            return true;
          }
          else if (board[p.first][p.second - 1].letter != ' ') {
            return true;
          }
        }
        else if (p.first == 0) { //left side
          if (board[p.first + 1][p.second].letter != ' ') {
            return true;
          }
          else if (board[p.first][p.second + 1].letter != ' ') {
            return true;
          }
          else if (board[p.first][p.second - 1].letter != ' ') {
            return true;
          }
        }
        else if (p.second == 14) { //bottom
          if (board[p.first + 1][p.second].letter != ' ') {
            return true;
          }
          else if (board[p.first - 1][p.second].letter != ' ') {
            return true;
          }
          else if (board[p.first][p.second - 1].letter != ' ') {
            return true;
          }
        }
        else if (p.second == 0) { //top
          if (board[p.first + 1][p.second].letter != ' ') {
            return true;
          }
          else if (board[p.first - 1][p.second].letter != ' ') {
            return true;
          }
          else if (board[p.first][p.second + 1].letter != ' ') {
            return true;
          }
        }
        else { //middle tiles
          if (board[p.first + 1][p.second].letter != ' ') {
            return true;
          }
          else if (board[p.first - 1][p.second].letter != ' ') {
            return true;
          }
          else if (board[p.first][p.second + 1].letter != ' ') {
            return true;
          }
          else if (board[p.first][p.second - 1].letter != ' ') {
            return true;
          }
        }
      }
      return false;
    }
    else { //first move - must go thru middle
      if (find(coords.begin(), coords.end(), center) != coords.end()) {
        firstMove = true;
        return true;
      }
      else {
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

  bool has_tile(char c) {
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

  void set_rack(vector<char> newRack) {
    rack = newRack;
  }

  int rack_size() {
    int n = rack.size();
    return n;
  }


};


class Game {
private:
  bool firstMove = false;
  vector<player> players;
  int num_players;
  Board board;
  bag scrabbleBag;
  int turnLimit;
  int pass;
public:
  Game(vector<player> players_list, int num, Board b, bag sb, int turns) {
    players = players_list;
    num_players = num;
    board = b;
    scrabbleBag = sb;
    turnLimit = turns;
    pass = 0;

    Game_loop(0);


  }





  void Game_loop(int player_num) {
    player& current = players[player_num]; //get current player


    cout << current.get_name() << "'s turn!" << endl;
    cout << "Score: " << current.get_score() << endl;
    //current.print_rack();
    int turnScore = 0;
    Board tempBoard = board; //allows us to attempt moves without editing the real board
    vector<char> tempRack = current.get_rack();

    vector<pair<int, int>> coords;
    while (true) { //player turn runs untill they end their turn - either drawing or making a move
      HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
      tempBoard.displayBoard();
      SetConsoleTextAttribute(hConsole, 15);
      cout << current.get_name() << "'s rack: ";
      for (char tile : tempRack) {
        int tileValue = tempBoard.getLetterValue(tile);
        std::cout << tile << ":" << tileValue << "/";
      }
      cout << "\n";

      SetConsoleTextAttribute(hConsole, 9);
      cout << "double letter score ";
      SetConsoleTextAttribute(hConsole, 6);
      cout << "triple letter score ";
      SetConsoleTextAttribute(hConsole, 10);
      cout << "double word score ";
      SetConsoleTextAttribute(hConsole, 12);
      cout << "triple word score " << endl;;
      SetConsoleTextAttribute(hConsole, 15);
      cout << "exchange - /exchange (number of letters to replace)" << endl; //LJ
      cout << "to place a tile - /place (x) (y) (letter)" << endl;
      cout << "to undo - /undo" << endl;
      cout << "to confirm moves & end turn - /end" << endl;
      cout << "to pass - /pass" << endl;

      //cout << "this code work" << endl;
      string input;
      getline(cin, input); //idk why this works better than cin >> lmao

      if (input.find("/exchange") != string::npos) {
        bool validInput = false;
        bool out = false;
        int Q = 0;
        while (!validInput && !out) {
          try {
            istringstream ss(input); //get args
            string input;
            getline(ss, input, ' ');
            getline(ss, input, ' ');// this line overwrites "input" from "/exchange" to the "number of letters to replace"
            int intput = stoi(input);
            vector <char> discardedTiles;
            if (scrabbleBag.remaining_tiles() < 7) {
              cout << "Not enough tiles in bag" << endl;
            }
            if (intput == 0) {
              cout << "exchange cancelled." << endl;
            }


            if (intput < 1 || intput > 7) {
              throw invalid_argument("Invalid number of letters to replace.");
            }
            while (Q < intput)
            {
              string str;
              cout << "Input letter to discard" << endl;
              getline(cin, str);

              char c = str[0];
              auto it = find(tempRack.begin(), tempRack.end(), c);

              if (it != tempRack.end()) {
                //delete tile from temporary rack


                discardedTiles.push_back(c);
                tempRack.erase(it);
                Q++;
              }
              else {
                cout << "letter was not in your rack try again" << endl;
              }
            }
            current.set_rack(tempRack);
            for (int i = 0; i < intput; i++)
            {
              current.add_tile(scrabbleBag);
            }
            for (int i = 0; i < discardedTiles.size(); i++)
            {
              scrabbleBag.return_tile(discardedTiles[i]);

            }
            discardedTiles.clear();
            scrabbleBag.shuffle_bag();
            //LJ
            validInput = true;
          }
          catch (const invalid_argument& e) {
            cout << "Invalid input: " << "Please check your formatting and try again." << endl;
            out = true;

          }
          catch (const exception& e) {
            cout << "Error: " << e.what() << ". Please try again." << endl;
            out = true;

          }
        }
        if (validInput)
        {
          pass = 0;
          break;
        }
      }
      if (input.find("/place") != string::npos) { //place tiles one by one
        istringstream ss(input); //get args
        bool validInput = false;
        bool out = false;
        while (!validInput && !out) {

          try {
            string x_s, y_s, c_s;
            getline(ss, x_s, ' ');
            getline(ss, x_s, ' ');
            getline(ss, y_s, ' ');
            getline(ss, c_s, ' ');
            //cout << x_s << y_s << c_s << endl;
            int x = stoi(x_s);
            int y = stoi(y_s);
            char c = c_s[0];
            auto it = find(tempRack.begin(), tempRack.end(), c);
            if (it != tempRack.end()) {
              //delete tile from temporary rack
              tempRack.erase(it);
              if (c == '_')
              {
                char blank;
                cout << "You selected a blank tile! Please input the character you'd like that blank to represent" << endl;
                cin >> blank;
                tempBoard.placeTile(y, x, blank);
              }
              else {
                tempBoard.placeTile(y, x, c);
              }
              coords.emplace_back(y, x);
            }
            else {
              cout << "Only use tiles from your rack!!" << endl;
            }

          }
          catch (const invalid_argument& e) {
            //cout << "Invalid input: " << "Please check your formatting and try again." << endl;
            out = true;

          }
          catch (const exception& e) {
            //cout << "Error: " << e.what() << ". Please try again." << endl;
            out = true;

          }
        }

      }
      else if (input.find("/undo") != string::npos) { //undo all tiles placed this turn;
        tempBoard = board; //revert to original board
        tempRack = current.get_rack();
        coords.clear();
      }
      else if (input.find("/end") != string::npos) { //check if placed tiles are valid
        //still need to check if tiles being played are in the player's rack & removing them from the rack once played
        //also must calculate score of turn


        turnScore = tempBoard.CheckBoard();
        //cout << turnScore;
        if (turnScore > 0 && board.checkMove(coords, firstMove)) {

          pass = 0;
          board = tempBoard;
          cout << "Good move!" << endl;
          cout << "Score for move: " << turnScore << endl;
          //board.calculateScore(coords);
          current.set_rack(tempRack);
          current.add_score(turnScore);
          firstMove = true;
          while (current.rack_size() < 7) {
            current.add_tile(scrabbleBag);
          }
          break;
        }
        else {
          tempBoard = board;
          tempRack = current.get_rack();
          cout << "Invalid move!" << endl;
          coords.clear();
        }
      }
      else if (input.find("/pass") != string::npos) {
        pass++;
        cout << "Player " << current.get_name() << " passed their turn." << endl;
        break;
      }
      else {
        cout << "please enter a valid input" << endl;
      }

    }

    if (noMoves()) { //if end game conditions are met
      endGame();
    }
    else if (player_num == num_players - 1) { //last player turn ended - go to first
      Game_loop(0);
    }
    else { //go to next player's turn
      Game_loop(player_num + 1);

    }
  }



  bool bagEmpty() {
    if (scrabbleBag.remaining_tiles() == 0)
      return true;
    else {
      cout << "Game bag contains " << scrabbleBag.remaining_tiles() << " tiles left." << endl;
      return false;
    }
  }


  bool noMoves() {

    if (num_players * 2 == pass) {
      return true;
    }
    else
      return false;
  }


  void endGame() {
    player winner = players[0];
    cout << "GAME OVER" << endl;
    for (int i = 0; i < num_players; i++) { //print players and find winner - need edge case for ties
      cout << players[i].get_name() << " : " << players[i].get_score() << endl;
      if (players[i].get_score() > winner.get_score()) {
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


  Game g(players, number_of_players, scrabbleBoard, scrabbleBag, 5);
  /*
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
  */

  return 0;

}


