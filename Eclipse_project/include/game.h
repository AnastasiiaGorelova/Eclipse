
#ifndef ECLIPSE_PROJECT_GAME_H
#define ECLIPSE_PROJECT_GAME_H

#include "game_fwd.h"
#include "space_ship.h"
#include <ctime>
#include <vector>

namespace eclipse {
struct Game {
private:
  double time;
  Game_state game_state = ONGOING;
  std::vector<std::vector<Field_state>> field;
  int lives = 3;
  Space_ship my_ship;

public:
  Game() {
    field.resize(WIDTH, std::vector<Field_state>(HEIGHT, NOTHING));
    for (int i = my_ship.where_is_ship().first - my_ship.get_size();
         i <= my_ship.where_is_ship().first + my_ship.get_size(); i++) {
      for (int j = my_ship.where_is_ship().second - my_ship.get_size();
           j < HEIGHT; j++) {
        field[i][j] = SPACE_SHIP;
      }
    }
    time = static_cast<double>(clock()) / static_cast<double>(CLOCKS_PER_SEC);
  }
  Game_state get_game_state() const;

  Field_state get_field_state(int x, int y) const;

  int get_time() const;
};
} // namespace eclipse

#endif // ECLIPSE_PROJECT_GAME_H
