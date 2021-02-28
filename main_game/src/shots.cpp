#include "shots.h"

namespace eclipse {
    std::pair<int, int> Shot::find_shot() const {
        return {x, y};
    }
    void Shot::move() {
        y -= speed;
    }
}// namespace eclipse