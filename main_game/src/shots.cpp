#include "include/shots.h"

namespace eclipse {
    std::pair<int, int> Shot::get_coordinates() const {
        return {x, y};
    }
    void Shot::move() {
        y -= speed;
    }
}// namespace eclipse