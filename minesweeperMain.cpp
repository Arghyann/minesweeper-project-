#include "minesweeper.hpp"
#include "UserBoard.hpp"
#include <iostream> 
#include <array> 

using namespace std;




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
                    //obj1.viewBoard(); //prints the solution board after initialising it
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
