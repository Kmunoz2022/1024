#include <iostream>
#include "Board.hpp"
using namespace std;

int main()
{
    Board game(3, 3); //create a Board object with 3 rows and 3 columns.
    game.start();
    return 0;
}