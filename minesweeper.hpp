#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

#include <iostream>
#include <vector>
#include <tuple>
#include <random>
#include <algorithm>
#include<chrono>
using namespace std;

class minesweeper {
public:
    int dimensions, noMines;
    vector<vector<char>> board;
    tuple<int,int> firstcord;

    minesweeper(int dimensionsInput, int Mines,int xfirstcord,int yfirstcord)
        : dimensions(dimensionsInput), noMines(Mines) {
        board.assign(dimensions, vector<char>(dimensions, '0'));
        firstcord=make_tuple(xfirstcord,yfirstcord);
        placeMines();
    }

    void placeMines() {
    vector<tuple<int, int>> cords;
    cords.clear();

    // Seed using current system time
    auto seed = chrono::system_clock::now().time_since_epoch().count();     //generating a seed did not give random number
    mt19937 rd(seed);                                                       //added current time to get a truly random board?

    uniform_int_distribution<int> distr(0, dimensions - 1); 
    int x, y;
    while (cords.size() != noMines) {
        x = distr(rd);
        y = distr(rd);
        tuple<int, int> coord = make_tuple(x, y);
        if (find(cords.begin(), cords.end(), coord) == cords.end() && firstcord != coord) {
            cords.push_back(coord);
            board[x][y] = 'X'; 
        }
    }
    generateScore();
}

    void viewBoard() {
        
    cout << "   ";
    for(int i = 0; i < dimensions; i++) {
        cout << i << "  ";
    }
    cout << endl;

    
    for(int i = 0; i < dimensions; i++) {
       
        cout << i << "  ";

        
        for (int j = 0; j < dimensions; j++) {
            cout << board[i][j] << "  ";
        }
        cout << endl;
    }
}
    void generateScore(){
        int count;
        for (int i = 0; i < dimensions; i++)
        {
            for (int j = 0; j < dimensions; j++)
            {   count=0;
                if (board[i][j]=='X') continue;
                for (int x = -1; x < 2; x++)
                {
                    for (int y = -1; y < 2; y++)
                    {   
                        if(i+x>dimensions-1||i+x<0||j+y<0||j+y>dimensions-1) continue;
                        if(board[i+x][j+y]=='X'){               // ' ' and " " mean two different things in cpp. Again, good job cpp!
                            count++;
                        }       
                    }
                    
                }
                board[i][j]=count + '0'; 

            }
            
        }
        
    }
};
#endif // MINESWEEPER_HPP