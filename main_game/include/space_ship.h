#ifndef MAIN_GAME_SPACE_SHIP_H
#define MAIN_GAME_SPACE_SHIP_H

#include "game_fwd.h"
#include <string>
#include <utility>

namespace eclipse {
    struct SpaceShip {
    private:
        const int size = 3;      // TODO: the exact coordinates
        int x = kWidth / 2 - size;//left corner coordinates
        int y = kHeight - size;
        std::string id = "ship";
        int speed = 2;

    public:
        std::pair<int, int> find_ship() const;//x,y coordinates
        int get_size() const;
        void move(MoveDirection direction);
    };
}// namespace eclipse

#endif//MAIN_GAME_SPACE_SHIP_H
