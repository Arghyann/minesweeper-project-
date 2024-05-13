#include <iostream>
#include <vector>
#include <random>
#include <tuple>
#include <algorithm>
#include<cmath>
#include<array>
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
        vector<tuple<int, int>> cords;                  //declared four variables and generated a seed from the os just to get two random numbers. Good job cpp!
        random_device rd;
        uniform_int_distribution<int> distr(0, dimensions - 1); 
        int x, y;
        while (cords.size() != noMines) {
            x = distr(rd);
            y = distr(rd);
            tuple<int, int> coord = make_tuple(x, y);
            if (find(cords.begin(), cords.end(), coord) == cords.end()&&firstcord!=coord) {
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

    void printUserBoard() const{     //const states that the object is not modified in this function
        
        cout << "   ";
        for (int i = 0; i < dimensions; ++i) {
            cout << i << "  ";
        }
        cout << endl;

        
        for (int i = 0; i < dimensions; ++i) {
            
            cout << i << "  ";

            
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
        if (msobject.board[x][y]=='X'){
            msobject.viewBoard();
            cout<<"You lose!";
            exit(0);
        }
        if((msobject.board[x][y]!='0')||x==0||y==0||x==dimensions-1||y==dimensions-1){
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
        size_t i;
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

int getIntInput(int minVal, int maxVal) {
    int input;
    while (true) {
        cout << "Enter an integer between " << minVal << " and " << maxVal << ": ";
        if (cin >> input && input >= minVal && input <= maxVal) {
            // Integer input within range
            break;
        } else {
            // Clear input stream and ignore invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer between " << minVal << " and " << maxVal << "." << endl;
        }
    }
    return input;
}

int main() {
    minesweeper obj1(1,1,1,1);                 //initialised to garbage values
    cout<<"Enter the dimensions of the board: ";
    int dimension= getIntInput(5,200);
    cout<<"Enter difficulty\n1)Easy->0\n2)Medium->1\n3)Hard->2\n";
    int difficulty=getIntInput(0,2);
    int density;
    switch (difficulty)
    {
    case 0:
        density=floor(0.1*dimension*dimension);
        break;
    case 1:
        density=floor(0.15*dimension*dimension);
        break;
    case 2:
        density=floor(0.2*dimension*dimension);
        break;    
    default:
        break;
    }
    int x,y;  //the co-ordinates for the very first mine 
    array<int,2> mineCord; //to hold mines temporarily after the user flags them
    UserBoard userboard(dimension,'.');
    userboard.printUserBoard();
    int move=0;                      //move counter so first move is never a mine
    while(true){
        cout<<"Options\n1)Flag a mine\n2)Reveal a cell\n3)Give up haha!\n";
        int choice=getIntInput(1,3);
        switch (choice)
        {
            case 1:
                cout<<"enter the co-ords of the cell you wanna flag one by one"<<endl;
                mineCord[0]=getIntInput(0,dimension-1);
                mineCord[1]=getIntInput(0,dimension-1);
                userboard.MineCordinates.push_back(mineCord);
                userboard.boardU[mineCord[0]][mineCord[1]]='X';
                userboard.printUserBoard();
                if(userboard.checkForWin(obj1)){
                    cout<<"You won!!";
                    exit(0);

                } 
                break;              
            case 2:
                cout<<"enter the cell you wanna reveal one by one\n";
                x=getIntInput(0,dimension-1);
                y=getIntInput(0,dimension-1);
                if (move==0){
                    obj1=minesweeper(dimension,density,x,y);
                    obj1.viewBoard();
                }
                userboard.revealcells(x,y,obj1);
                userboard.printUserBoard();
                move++;
                
                
                break;
            case 3: 
                return 0;
                break;
            
            default:
                break;
        }
    }
    
    
        

    
}
