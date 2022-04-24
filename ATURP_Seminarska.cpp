// ATURP_Seminarska.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
using namespace std;

class Puzzle { 
public:
    array<int, 9> board;
    int blankSpace;

    Puzzle(array<int, 9> input, int blank) {
        board = input;
        blankSpace = blank;
    }

};

int main() {
    int cases = 0;
    int blankTemp;
    vector<Puzzle> boards;
    array<int, 9> board;
    ifstream myfile("sample.in");
    if (myfile.is_open())
    {
        myfile >> cases;
        for(int j = 0; j < cases; j++){
            for (int i = 0; i < 9; i++) {
                myfile >> board[i];
                if (board[i] == 0)
                    blankTemp = i;
            }
            boards.push_back(Puzzle(board, blankTemp));
        }
    }
    else cout << "Unable to open file";
    for (int i = 0; i < cases; i++) {
        Puzzle currentProblem = boards[0];

    }
    return 0;
}
