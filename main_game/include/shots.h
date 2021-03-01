#ifndef MAIN_GAME_SHOTS_H
#define MAIN_GAME_SHOTS_H

#include "game_fwd.h"
#include "space_ship.h"
#include <string>
#include <utility>

namespace eclipse {
    struct Shot {
    private:
        int size = 1;
        int x;
        int y;
        int speed = 1;
        std::string id;

    public:
        Shot(int x, int y, std::string id) : x(x), y(y), id(std::move(id)) {}
        std::pair<int, int> get_coordinates() const;
        void move();
    };
}// namespace eclipse

#endif//MAIN_GAME_SHOTS_H