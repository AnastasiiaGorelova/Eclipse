#ifndef MAIN_GAME_ASTEROIDS_H
#define MAIN_GAME_ASTEROIDS_H

#include "game_fwd.h"
#include <cstdlib>
#include <utility>
#include "asteroids_presentation.h"

namespace eclipse {
    struct Asteroid {
        Asteroid(Asteroids_presentation* present_) : present(present_) {}

    private:
        const int size = rand() % 5 + 1;
        int x = rand() % WIDTH;
        int y = 0;
        int shots_to_die = size;
        const int speed = 2;
        Object_state cur_state = ALIVE;

        Asteroids_presentation* present;

    public:
        Object_state get_state() const;

        void set_asteroid_in_field(int x, int y, int size);

        int get_speed() const;

        void move();

        std::pair<int, int> where_is_asteroid() const;//x,y coordinates

        int get_size() const;

        void killer();
    };

}// namespace eclipse

#endif//MAIN_GAME_ASTEROIDS_H
