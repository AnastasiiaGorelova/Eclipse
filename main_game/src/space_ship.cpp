
#include "../include/space_ship.h"
#include "../include/game.h"
#include <utility>

namespace eclipse {
    namespace {
        void moving(int &x, int vec, int size = 0) {
            if (x + vec >= WIDTH - size) {
                x = WIDTH - size;
            } else if (x + vec <= 0) {
                x = 0;
            } else {
                x += vec;
            }
        }
    }// namespace
    std::pair<int, int> Space_ship::where_is_ship() const {
        return std::make_pair(Space_ship::x, Space_ship::y);
    }
    int Space_ship::get_size() const { return Space_ship::size; }

    void Space_ship::move(Go direction = NO_MOVE) {
        switch (direction) {
            case NO_MOVE:
                return;
            case LEFT:
                moving(x, -speed, size);
            case RIGHT:
                moving(x, speed);
        }
    }

}// namespace eclipse