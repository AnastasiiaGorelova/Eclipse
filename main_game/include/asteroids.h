#ifndef MAIN_GAME_ASTEROIDS_H
#define MAIN_GAME_ASTEROIDS_H

#include "game_fwd.h"
#include <cstdlib>
#include <string>
#include <utility>

namespace eclipse {
    struct Asteroid {
    private:
        int x;
        int y = 0;
        int size = 0;
        int shots_to_die;
        ObjectState cur_state = kAlive;
        std::string id;

    public:
        Asteroid(int x, int size, std::string id) : x(x), size(size), shots_to_die(size), id(std::move(id)) {}

        ObjectState get_state() const;

        void move(int speed);

        std::pair<int, int> find_asteroid() const;//x,y coordinates

        int get_size() const;

        void kill();
    };

}// namespace eclipse

#endif//MAIN_GAME_ASTEROIDS_H
