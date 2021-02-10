#include "../include/game.h"
#include "../include/game_fwd.h"
#include <iostream>

int main() {
  eclipse::Game g;

  // only for debug
  for (int j = 0; j < eclipse::HEIGHT; j++) {
    for (int i = 0; i < eclipse::WIDTH; i++) {
      if (g.get_field_state(i, j) == eclipse::NOTHING)
        std::cout << '.';
      else if (g.get_field_state(i, j) == eclipse::ASTEROID)
        std::cout << 'O';
      else if (g.get_field_state(i, j) == eclipse::SPACE_SHIP)
        std::cout << 'X';
      else
        std::cout << 'L';
    }
    std::cout << '\n';
  }
  std::cout << g.get_time() << '\n';
  // finished

  return 0;
}
