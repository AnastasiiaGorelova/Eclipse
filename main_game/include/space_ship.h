#ifndef MAIN_GAME_SPACE_SHIP_H
#define MAIN_GAME_SPACE_SHIP_H

#include <string>
#include <utility>
#include "game_fwd.h"

namespace eclipse {
struct spaceship {
private:
    int size = 150;
    int x;
    int y;
    std::string id = "abcd";
    int speed = 2;

public:
    spaceship(int width, int height) : x(width / 2 - size), y(height - size) {
    }
    std::pair<int, int> get_coordinates() const;
    std::string get_id() const;
    int get_size() const;
    void move(MoveDirection direction);
};
}  // namespace eclipse

#endif  // MAIN_GAME_SPACE_SHIP_H