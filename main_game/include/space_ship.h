#ifndef MAIN_GAME_SPACE_SHIP_H
#define MAIN_GAME_SPACE_SHIP_H

#include "game_fwd.h"
#include <string>
#include <utility>

namespace eclipse {
    struct SpaceShip {
    private:
        int size = 3;
        int x;
        int y;
        std::string id = "ship";
        int speed = 2;

    public:
        SpaceShip(int width, int height) : x(width / 2 - size), y(height - size) {}
        std::pair<int, int> find_ship() const;
        int get_size() const;
        void move(MoveDirection direction);
    };
}// namespace eclipse

#endif//MAIN_GAME_SPACE_SHIP_H
