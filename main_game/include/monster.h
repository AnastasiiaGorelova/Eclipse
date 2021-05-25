#ifndef MAIN_GAME_MONSTER_H
#define MAIN_GAME_MONSTER_H

#include <string>
#include "game_fwd.h"

namespace eclipse {
    struct monster {
    private:
        int size = 150;
        int x;
        int y = 0;
        std::string id;
        int speed = 16;
    public:
        monster(int width, std::string id) : x(width / 2 - size / 2), id(std::move(id)) {
        }
        std::pair<int, int> get_coordinates() const;
        std::string get_id() const;
        int get_size() const;
        void move(MoveDirection direction);
    };
}


#endif//MAIN_GAME_MONSTER_H
