
#include "../include/asteroids.h"
#include "../include/game_window.h"

extern Ui::game_window game_window;

namespace eclipse {
    Object_state Asteroid::get_state() const {
        return cur_state;
    }
    int Asteroid::get_speed() const {
        return speed;
    }
    void Asteroid::move() {
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
    void Asteroid::set_asteroid_in_field(int x, int y, int size) {
        present->set_asteroid(x, y, size);
//        game_window
    }
}// namespace eclipse