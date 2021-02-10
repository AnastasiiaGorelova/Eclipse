#include "../include/space_ship.h"
#include <utility>

namespace eclipse {
std::pair<int, int> Space_ship::where_is_ship() const {
  return std::make_pair(Space_ship::x, Space_ship::y);
}
int Space_ship::get_size() const { return Space_ship::size; }
} // namespace eclipse