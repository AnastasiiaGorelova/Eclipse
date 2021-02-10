
#ifndef ECLIPSE_PROJECT_SPACE_SHIP_H
#define ECLIPSE_PROJECT_SPACE_SHIP_H

#include "game_fwd.h"
#include <utility>

namespace eclipse {
struct Space_ship {
private:
  static const int size = 1; // TODO: the exact coordinates
  int x = WIDTH / 2;         // central coordinates
  int y = HEIGHT - size - 1;

public:
  void shoot() {}
  std::pair<int, int> where_is_ship() const;
  int get_size() const;
};
} // namespace eclipse
#endif // ECLIPSE_PROJECT_SPACE_SHIP_H
