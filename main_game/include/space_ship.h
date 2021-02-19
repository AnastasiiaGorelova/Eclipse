
#ifndef MAIN_GAME_SPACE_SHIP_H
#define MAIN_GAME_SPACE_SHIP_H

#include "game_fwd.h"
#include <utility>

namespace eclipse {
    struct Space_ship {
    private:
        const int size = 3;      // TODO: the exact coordinates
        int x = WIDTH / 2 - size;//left corner coordinates
        int y = HEIGHT - size;

    public:
        std::pair<int, int> where_is_ship() const;//x,y coordinates
        int get_size() const;
    };
}// namespace eclipse

#endif//MAIN_GAME_SPACE_SHIP_H
