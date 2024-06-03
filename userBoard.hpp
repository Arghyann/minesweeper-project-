#ifndef USERBOARD_HPP
#define USERBOARD_HPP

#include <iostream>
#include <vector>
#include <array>
#include "minesweeper.hpp"
using namespace std;

class UserBoard {
public:
    int dimensions;
    vector<vector<char>> boardU;
    vector<vector<bool>> visited;
    vector<array<int,2>> MineCordinates;

    
    UserBoard(int dimensions, char x) : dimensions(dimensions) {
        boardU.assign(dimensions, vector<char>(dimensions, x));
        visited.assign(dimensions,vector<bool>(dimensions,false));

    }

    void printUserBoard() const {                   //const states that the object is not modified in this call
        cout << "    ";
        for (int i = 0; i < dimensions; ++i) {
            if (i < 10) {
                cout << i << "  ";
            } else {
                cout << i << " ";
            }
        }
        cout << endl;

        for (int i = 0; i < dimensions; ++i) {
            if (i < 10) {
                cout << i << "   ";
            } else {
                cout << i << "  ";
            }

            for (int j = 0; j < dimensions; ++j) {
                cout << boardU[i][j] << "  ";
            }
            cout << endl;
        }
}     
    void revealcells(int x ,int y,minesweeper& msobject){      //passing minesweeper object as a parameter
        if(visited[x][y]){
            return;

        }
        visited[x][y]=true;                                     //updated visted first thing
        if(msobject.board[x][y]=='0') boardU[x][y]='0';
        if (msobject.board[x][y]=='X'){
            msobject.viewBoard();
            cout<<"You lose!";
            exit(0);
        }
        if(x<0||y<0||x>dimensions-1||y>dimensions-1) return;        //overflow and stuff handled
        if((msobject.board[x][y]!='0')){
            boardU[x][y]=msobject.board[x][y];

            
        }
        else{
            //scout<<"check if it enters this part of the code.";
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)                                            //recursively reveal cells in all 8 directions until a number is encountered! Recursion is fun 
                {
                    
                    if(i+x<=dimensions-1&&i+x>-1&&j+y>-1&&j+y<=dimensions-1){
                        revealcells(x+i,y+j,msobject);
                    }
                }
                
            }
            

        }
        
    }
    bool checkForWin(minesweeper& msobject){
        size_t i=0;
        bool flag=false;
        int NumberofMines=msobject.noMines;
        
        int NumberofUserMines=MineCordinates.size();
        
        if(NumberofMines==NumberofUserMines){
            for (i = 0; i <NumberofMines; i++)
            {   
                if(msobject.board[MineCordinates[i][0]][MineCordinates[i][1]]=='X') continue;
                break;
            }
            
        }
        if(i==NumberofMines) return true;
        return false;    
    
    }
};

#endif // USERBOARD_HPP