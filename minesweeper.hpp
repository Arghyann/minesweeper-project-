#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

#include <iostream>
#include <vector>
#include <tuple>
#include <random>
#include <algorithm>
#include<chrono>
#include<unordered_set>
using namespace std;

class minesweeper {
private:
   bool isCordinVector(vector<tuple<int,int>>& v, tuple<int,int> cord) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] == cord) {
            return true;
        }
    }
    return false;
}

public:
    int dimensions, noMines;
    vector<vector<char>> board;
    
    vector<tuple<int,int>> avoidCoords;

    minesweeper(int dimensionsInput, int Mines,int xfirstcord,int yfirstcord)
        : dimensions(dimensionsInput), noMines(Mines) {
        board.assign(dimensions, vector<char>(dimensions, '0'));
        if(dimensions!=1){
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <=1; j++)
            {
                int newX = xfirstcord + i;
                int newY = yfirstcord + j;

                
                if (newX >= 0 && newX < dimensions && newY >= 0 && newY < dimensions) {
                    avoidCoords.push_back(make_tuple(newX, newY));
                }
            }
            
        }
        /*cout << "Avoid Coordinates: ";
        for (const auto& coord : avoidCoords) {
        cout << "(" << get<0>(coord) << ", " << get<1>(coord) << ") ";
        }
        cout << endl;*/}
        placeMines();
    }

    void placeMines() {
        // Seed using current system time because the normal one wasn't random enough i hate this language
        
        auto seed = chrono::system_clock::now().time_since_epoch().count();
        mt19937 rd(seed);

        
        uniform_int_distribution<int> distr(0, dimensions - 1);

        int minesPlaced = 0;
        while (minesPlaced < noMines) {
            int x = distr(rd);
            int y = distr(rd);

            
            bool nearFirstMove = isCordinVector(avoidCoords, make_tuple(x, y));

            
            if (!nearFirstMove && board[x][y] == '0') {
               
                board[x][y] = 'X';
                minesPlaced++;
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