#include <iostream>
#include <vector>
#include <random>
#include <tuple>
#include <algorithm>
#include<cmath>

using namespace std;

class minesweeper {
public:
    int dimensions, noMines;
    vector<vector<char>> board;

    minesweeper(int dimensionsInput, int Mines)
        : dimensions(dimensionsInput), noMines(Mines) {
        board.assign(dimensions, vector<char>(dimensions, '0')); 
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
            if (find(cords.begin(), cords.end(), coord) == cords.end()) {
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
    vector<vector<char>> board;

    // Constructor to generate user board
    UserBoard(int dimensions, char x) : dimensions(dimensions) {
        board.assign(dimensions, vector<char>(dimensions, x));
    }

    void printUserBoard() const {
        // Print column indices
        cout << "   ";
        for (int i = 0; i < dimensions; ++i) {
            cout << i << "  ";
        }
        cout << endl;

        // Print the board
        for (int i = 0; i < dimensions; ++i) {
            // Print row index
            cout << i << "  ";

            // Print the contents of each cell
            for (int j = 0; j < dimensions; ++j) {
                cout << board[i][j] << "  ";
            }
            cout << endl;
        }
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
    minesweeper obj1(dimension,density);
    obj1.viewBoard();
    UserBoard userboard(dimension,'.');
    userboard.printUserBoard();
    while(true){
        cout<<"Options\n1)Flag a mine\n2)Reveal a cell\n3)Give up haha!\n";
        int choice=getIntInput(1,3);
    }
    
    
        

    
}
