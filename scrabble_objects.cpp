#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <bits/stdc++.h>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <utility>
#include <map>

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
public:
    char letter;
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    vector<pair<int,int>> doubleLetterScore = { {0, 3}, {0, 11}, {2,6}, {2,8},{3,0},{3,7},{3,14},{6,2},{6,6},{6,8},{6,12},{7,3},{7,11},{8,2},{8,6},{8,8},{8,12},{11,0},{11,7},{11,14},{12,6},{12,8},{14,3},{14,11} };
    vector<pair<int,int>> tripleLetterScore = {{1,5},{1,9},{5,1},{5,5},{5,9},{5,13},{9,1},{9,1},{9,5},{9,9},{9,13},{13,5},{13,9}};
    vector<pair<int,int>> doubleWordScore = {{1,1},{2,2},{3,3},{4,4},{1,13},{2,12},{3,11},{4,10},{13,1},{12,2},{11,3},{10,4},{13,13},{12,12},{11,11},{10,10}};
    vector<pair<int,int>> tripleWordScore = {{0,0},{0,7},{0,14},{7,0},{7,14},{14,0},{14,7},{14,14}};
    Board()
    {
        //board.resize(15, vector<char>(15, ' '));

        initializeTiles();
    }
    void initializeTiles()
    {
        for (int i = 0; i < 15; i++)
        {
            for(int j = 0; j < 15; j++)
                if(find(doubleLetterScore.begin(), doubleLetterScore.end(), make_pair(i, j)) != doubleLetterScore.end())
                {
                    board[i][j].value = 1;
                    board[i][j].letter = ' ';
                }
            else if(find(tripleLetterScore.begin(), tripleLetterScore.end(), make_pair(i, j)) != tripleLetterScore.end())
            {
                board[i][j].value = 2;
                board[i][j].letter = ' ';
            }
            else if(find(doubleWordScore.begin(), doubleWordScore.end(), make_pair(i, j)) != doubleWordScore.end())
            {
                board[i][j].value = 3;
                board[i][j].letter = ' ';
            }
                else if(find(tripleWordScore.begin(), tripleWordScore.end(), make_pair(i, j)) != tripleWordScore.end())
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
        for(int i =0 ; i < 15 ; i++)
        {
            for (int j=0 ; j<15 ; j++)
            {
                int k = board[i][j].value;
                if (board[i][j].letter == ' ') {
                    SetConsoleTextAttribute(hconsole, k);
                    cout << "0" << " ";
                } else {
                    SetConsoleTextAttribute(hconsole, k);
                    cout <<  board[i][j].letter << " ";
                }

            //cout << i << "," << j << " ";
            }
            cout << endl;
        }

    }

    void placeTile(int row, int col, char letter)
    {
        board[row][col].letter = letter;
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
                {'A', 9}, {'B', 2}, {'C', 2}, {'D', 4}, {'E', 12}, {'F', 2},
                {'G', 3}, {'H', 2}, {'I', 9}, {'J', 1}, {'K', 1}, {'L', 4},
                {'M', 2}, {'N', 6}, {'O', 8}, {'P', 2}, {'Q', 1}, {'R', 6},
                {'S', 4}, {'T', 6}, {'U', 4}, {'V', 2}, {'W', 2}, {'X', 1},
                {'Y', 2}, {'Z', 1}, {'_', 2}
        };
        for (auto &tile : tile_distribution) {
            for (int i = 0; i < tile.second; ++i) {
                tiles.push_back(tile.first);
            }
        }


        srand(time(0));
        random_shuffle(tiles.begin(), tiles.end());

        char draw_tile() {
            if (tiles.empty()) {
                throw std::runtime_error("Tile bag is empty.");
            }
            char tile = tiles.back();
            tiles.pop_back();
            return tile;
        }

        bool is_empty() {
            return tiles.empty();
        }

        int remaining_tiles() {
            return tiles.size();
        }
};

class player
{
private:
    string name;
    int score;
public:
    char tiles[7];


    void placeTiles()
    {

    }

};
int main() {

    ///start game loop

    Board scrabbleBoard; /// initialize board
    bag scrabbleBag;

    scrabbleBoard.placeTile(7, 7, 'S');
    scrabbleBoard.placeTile(7, 8, 'C');
    scrabbleBoard.placeTile(7, 9, 'R');
    scrabbleBoard.placeTile(7, 10, 'A');
    scrabbleBoard.placeTile(7, 11, 'B');
    scrabbleBoard.placeTile(7, 12, 'B');
    scrabbleBoard.placeTile(7, 13, 'L');
    scrabbleBoard.placeTile(7, 14, 'E');

    scrabbleBoard.displayBoard();

    return 0;
}
