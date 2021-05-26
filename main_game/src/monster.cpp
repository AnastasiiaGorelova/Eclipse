#include "monster.h"

namespace eclipse {

    std::pair<int, int> monster::get_coordinates() const {
        return {x, y};
    }

    std::string monster::get_id() const {
        return id;
    }

    int monster::get_size() const {
        return size;
    }

    void monster::move(MoveDirection new_direction = kNoMove) {
        if (new_direction == kNoMove) {
            if (steps_to_one_side >= 25) {
                steps_to_one_side = 0;
                if (random_number(0, 1) == 1) {
                    direction = kRight;
                } else {
                    direction = kLeft;
                }
            }
            if (direction == kLeft) {
                x = std::max(x - speed, 0);
            } else {
                x = std::min(x + speed, kWidth - 1 - size);
            }
            steps_to_one_side++;
        }
        if (new_direction == kDown) {
            y += speed / 2;
            if (y >= kHeight / 10) {
                y = kHeight / 10;
                state = On_the_field;
                set_hearts();
            }
        }
        if (new_direction == kUp) {
            y -= speed / 2;
            if (y <= 0) {
                y = 0;
                state = Not_on_the_field;
            }
        }
    }

    MonsterState monster::get_state() const {
        return state;
    }

    void monster::change_state(MonsterState new_state) {
        state = new_state;
    }

    void monster::decrease_lives() {
        lives--;
        if (lives == 0) {
            state = Leaving;
        }
    }

    void monster::set_hearts() {
        lives = 5;
        int heart_size = size / lives;//скорректировать размеры
        int heart_y = y - heart_size;
        int heart_x = 0;
        for (int i = 0; i < lives; i++) {
            heart_coordinates.emplace_back(alien_heart{heart_x, heart_y, heart_size, new_uuid()});
            heart_x += heart_size;
        }
    }

}// namespace eclipse