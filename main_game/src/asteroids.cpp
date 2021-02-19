
#include "../include/asteroids.h"

namespace eclipse {
    Object_state Asteroid::get_state() const {
        return cur_state;
    }
    void Asteroid::move(int speed) {
        y += speed;
    }
    std::pair<int, int> Asteroid::where_is_asteroid() const {
        return std::make_pair(x, y);
    }
    int Asteroid::get_size() const {
        return size;
    }
    void Asteroid::killer() {
        --shots_to_die;
        if (!shots_to_die) {
            cur_state = DEAD;
        }
    }
}// namespace eclipse