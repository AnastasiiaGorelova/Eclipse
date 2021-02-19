#ifndef MAIN_GAME_ASTEROIDS_H
#define MAIN_GAME_ASTEROIDS_H

#include "game_fwd.h"
#include <cstdlib>
#include <utility>

namespace eclipse {
    struct Asteroid {
    private:
        int size;
        int x;
        int y = 0;
        int shots_to_die;
        Object_state cur_state = ALIVE;

    public:
        Asteroid(int x_, int size_) : x(x_), size(size_), shots_to_die(size_) {}

        Object_state get_state() const;

        void move(int speed);

        std::pair<int, int> where_is_asteroid() const;//x,y coordinates

        int get_size() const;

        void killer();
    };

}// namespace eclipse

#endif//MAIN_GAME_ASTEROIDS_H
