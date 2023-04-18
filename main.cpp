#include <iostream>
#include <vector>
#include <string>
using namespace std;



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

class tile
{

};


std::string getPlaceValueColorCode(int row, int col) {
    // Add your custom logic to determine the place values for different positions
    if (/* Double Letter */) {
        return "\033[34m"; // Blue
    } else if (/* Triple Letter */) {
        return "\033[32m"; // Green
    } else if (/* Double Word */) {
        return "\033[33m"; // Yellow
    } else if (/* Triple Word */) {
        return "\033[31m"; // Red
    } else {
        return "\033[37m"; // White
    }
}
class Board
{
private:
    vector<vector<char>> board;
public:

    Board()
    {
        board.resize(15, vector<char>(15, ' '));


    }

void displayBoard()
{
    for(int i =0 ; i < 15 ; i++)
    {
        for (int j=0 ; j<15 ; j++)
        {
            cout << (board[i][j] == ' ' ? '.' : board[i][j]) << " ";
        }
        cout << endl;
    }

}

void placeTile(int row, int col, char letter)
{
board[row][col] = letter;
}

};
class bag
{

};

int main() {
    Board scrabbleBoard;

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
