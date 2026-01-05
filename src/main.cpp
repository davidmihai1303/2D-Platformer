// INFO

// "Code" keyword inside comments means that part of code will be deleted and better implemented in the future. The keyword is used to better group scattered code
// Code=1 // Player hit-area box creation.
// Code=2 // Note vector declaration and utilization inside World class.
// Code=3 // Enemy default facing direction should not be the same for all enemies. It depends on the level/map

// Will be using  (*p).  instead of  p->  for better visualization of variable types.

// Variables starting with "m_" are member variables of the class / parent class

//TODO throw errors if player is not found inside the World class

#include "Game.hpp"

int main() {
    Game game;
    game.run();
    return 0;
}
