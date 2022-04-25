// ATURP_Seminarska.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <stack>
using namespace std;

class Puzzle { 
public:
    array<int, 9> board;
    int blankSpace;
    int h = 0;
    Puzzle(array<int, 9> input, int blank) {
        board = input;
        blankSpace = blank;
    }
    Puzzle(int h) {
        this->h = h;
    }

    void swap(int x, int y) {
        int temp = board[x];
        board[x] = board[y];
        board[y] = temp;
    }

    void heuristic(int g) {
        int h = 0;
        for (int i = 1; i <= 8 ; i++)
        {
            if (board[i - 1] != i) 
            {
                h++;
            }
        }
        if (board[8] != 0) {
            h++;
        }
        this->h = h + g;
    }

    bool isFinished() {
        for (int i = 0; i < 8; i++) {
            if (board[i] != i + 1)
                return false;
        }
        return true;
    }
};


int main() {
    int cases = 0;
    int blankTemp;
    vector<Puzzle> boards;
    vector<Puzzle> options;
    array<int, 9> board;
    ifstream myfile("sample.in");
    if (myfile.is_open())
    {
        myfile >> cases;
        for(int j = 0; j < cases; j++)
        {
            for (int i = 0; i < 9; i++) 
            {
                myfile >> board[i];
                if (board[i] == 0)
                    blankTemp = i;
            }
            boards.push_back(Puzzle(board, blankTemp));
        }
    }
    else cout << "Unable to open file";
    for (int i = 0; i < cases; i++) //tu gres skozi vse puzzle
    {
        Puzzle currentProblem = boards[i]; // trenutni puzzle
        int g = 1;
        while (!currentProblem.isFinished()) 
        {
            Puzzle swapped = currentProblem;
            switch (currentProblem.blankSpace) //v options so vsi možni premiki, glede na prazno mesto pac switch stavek tu
            {
            case 0:                
                swapped.swap(0, 1);
                swapped.blankSpace = 1;
                options.push_back(swapped);
                swapped = currentProblem;
                swapped.swap(0, 3);
                swapped.blankSpace = 3;
                options.push_back(swapped);
                break;
            case 1:
                swapped.swap(0, 1);
                swapped.blankSpace = 0;
                options.push_back(swapped);
                swapped = currentProblem;
                swapped.swap(1, 2);
                swapped.blankSpace = 2;
                options.push_back(swapped);
                swapped = currentProblem;
                swapped.swap(1, 4);
                swapped.blankSpace = 4;
                options.push_back(swapped);
                break;
            case 2:
                swapped.swap(2, 1);
                swapped.blankSpace = 1;
                options.push_back(swapped);
                swapped = currentProblem;
                swapped.swap(2, 5);
                swapped.blankSpace = 5;
                options.push_back(swapped);
                break;
            case 3:
                swapped.swap(0, 3);
                swapped.blankSpace = 0;
                options.push_back(swapped);
                swapped = currentProblem;
                swapped.swap(3, 4);
                swapped.blankSpace = 4;
                options.push_back(swapped);
                swapped = currentProblem;
                swapped.swap(3, 6);
                swapped.blankSpace = 6;
                options.push_back(swapped);
                break;
            case 4:
                swapped.swap(1, 4);
                swapped.blankSpace = 1;
                options.push_back(swapped);
                swapped = currentProblem;
                swapped.swap(3, 4);
                swapped.blankSpace = 3;
                options.push_back(swapped);
                swapped = currentProblem;
                swapped.swap(5, 4);
                swapped.blankSpace = 5;
                options.push_back(swapped);
                swapped = currentProblem;
                swapped.swap(4, 7);
                swapped.blankSpace = 7;
                options.push_back(swapped);
                break;
            case 5:
                swapped.swap(2, 5);
                swapped.blankSpace = 2;
                options.push_back(swapped);
                swapped = currentProblem;
                swapped.swap(5, 4);
                swapped.blankSpace = 4;
                options.push_back(swapped);
                swapped = currentProblem;
                swapped.swap(8, 5);
                swapped.blankSpace = 8;
                options.push_back(swapped);
                break;
            case 6:
                swapped.swap(3, 6);
                swapped.blankSpace = 3;
                options.push_back(swapped);
                swapped = currentProblem;
                swapped.swap(6, 7);
                swapped.blankSpace = 7;
                options.push_back(swapped);
                break;
            case 7:
                swapped.swap(6, 7);
                swapped.blankSpace = 6;
                options.push_back(swapped);
                swapped = currentProblem;
                swapped.swap(7, 4);
                swapped.blankSpace = 4;
                options.push_back(swapped);
                swapped = currentProblem;
                swapped.swap(7, 8);
                swapped.blankSpace = 8;
                options.push_back(swapped);
                break;
            case 8:
                swapped.swap(5, 8);
                swapped.blankSpace = 5;
                options.push_back(swapped);
                swapped = currentProblem;
                swapped.swap(8, 7);
                swapped.blankSpace = 7;
                options.push_back(swapped);
                break;
            }
            Puzzle min = Puzzle(1000);
            for (int stack = 0; stack < options.size(); stack++) //tu zracunas hevristiko za vsako potezo od vseh moznih pa zberes najmanjso torej najboljso
            {
                options[stack].heuristic(g);
                if (options[stack].h < min.h)
                    min = options[stack];
            }
            options.clear();
            currentProblem = min;
            g++;
        }
        int srok = 5;
    }
    return 0;
}
