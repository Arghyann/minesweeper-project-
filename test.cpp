/*#include"minesweeper.hpp"
#include<iostream>
int main(){
    minesweeper obj(5,2,2,2);
    obj.viewBoard();
    minesweeper obj2(5,2,1,1);
    obj2.viewBoard();
    minesweeper obj3(7,4,2,2);
    obj3.viewBoard();
    minesweeper obj4(7,4,1,1);
    obj4.viewBoard();
    
}*/
/*TODO 
1) Work on the random board generation
2)First move cannot be a number so clear the cells around the first move 
3)Unexpectedy triggers a win for n=7(check for the win function!)
*/
#include <iostream>
#include <random>
#include <chrono>

int main() {
    // Use system time as a seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    
    // Create a random number engine using the seed
    std::mt19937 gen(seed);
    
    // Create a uniform distribution to generate numbers in the range [0, 9]
    std::uniform_int_distribution<int> distr(0, 9);

    // Generate and print a random number
    int random_number = distr(gen);
    std::cout << "Random number: " << random_number << std::endl;

    return 0;
}
