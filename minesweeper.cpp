#include <iostream>
#include <vector>
#include <random>
#include <tuple>
#include <algorithm>
using namespace std;

class minesweeper {
public:
    int dimensions, noMines;
    vector<vector<char>> board;

    minesweeper(int dimensionsInput, int Mines)
        : dimensions(dimensionsInput), noMines(Mines) {
        board.assign(dimensions, vector<char>(dimensions, '0')); // Initialize with dimensions x dimensions
        placeMines();
    }

    void placeMines() {
        vector<tuple<int, int>> cords;
        random_device rd;
        uniform_int_distribution<int> distr(0, dimensions - 1); // Adjusted the range for the board dimensions
        int x, y;
        while (cords.size() != noMines) {
            x = distr(rd);
            y = distr(rd);
            tuple<int, int> coord = make_tuple(x, y);
            if (find(cords.begin(), cords.end(), coord) == cords.end()) {
                cords.push_back(coord);
                board[x][y] = 'X'; // Use 'X' to represent mines
            }
        }
    }

    void viewBoard() {
        for (int i = 0; i < dimensions; i++) {
            for (int j = 0; j < dimensions; j++) {
                cout << board[i][j] << "  ";
            }
            cout << "\n";
        }
    }
};

int main() {
    minesweeper obj1(10,50);
    obj1.viewBoard();
    return 0;
}
dsfsfs