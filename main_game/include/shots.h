
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

        friend class Game;

    public:
        Shot(int x_, int y_, std::string id_) : x(x_), y(y_), id(id_) {}
        std::pair<int, int> where_is_shot() const;
        void move();
    };
}// namespace eclipse

#endif//MAIN_GAME_SHOTS_H
