
#include "asteroids.h"

namespace eclipse {
    ObjectState Asteroid::get_state() const {
        return cur_state;
    }
    void Asteroid::move(int speed) {
        y += speed;
    }
    std::pair<int, int> Asteroid::find_asteroid() const {
        return {x, y};
    }
    int Asteroid::get_size() const {
        return size;
    }
    void Asteroid::kill() {
        --shots_to_die;
        if (!shots_to_die) {
            cur_state = kDead;
        }
    }
}// namespace eclipse