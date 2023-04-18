#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

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




class Board
{
private:
    vector<vector<char>> board;
public:
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);

    enum PlaceValue {
        Normal,
        DoubleLetter;
        TripleLetter;
        DoubleWord;
        TripleWord;
    };


    Board()
    {
        board.resize(15, vector<char>(15, ' '));


    }

    void displayBoard()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        for(int i =0 ; i < 15 ; i++)
        {
            for (int j=0 ; j<15 ; j++)
            {
                int k = getTileColorCode(i,j);
                if (board[i][j] == ' ') {
                    SetConsoleTextAttribute(hconsole, k);
                    cout <<  k << " ";
                } else {
                    SetConsoleTextAttribute(hconsole, k);
                    cout <<  board[i][j] << " ";
                }

            //cout << i << "," << j << " ";
            }
            cout << endl;
        }

    }

    void placeTile(int row, int col, char letter)
    {
        board[row][col] = letter;
    }
    int getTileColorCode(int row, int col) {

        // Add your custom logic to determine the place values for different positions
        if ((row == 0 && col == 0)||(row == 0 && col == 7)||(row == 0 && col == 14)) {// double letter score
            return 1; // Blue
        } else if ((row == 7 && col == 0)||(row == 7 && col == 7)||(row == 7 && col == 14)) {
            return 1; // Green
        } else if ((row == 14 && col == 0)||(row == 14 && col == 7)||(row == 14 && col == 14)) {
            return 1; // Yellow
        } else if (5==6) {
            return SetConsoleTextAttribute(hconsole, 1); // Red
        } else {
            return 7; // White
        }

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
