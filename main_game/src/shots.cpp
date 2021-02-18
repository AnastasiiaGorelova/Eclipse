#include "../include/shots.h"
namespace eclipse {
    std::pair<int, int> Shot::where_is_shot() const {
        return std::make_pair(x, y);
    }
    void Shot::move() {
        y -= speed;
    }
}// namespace eclipse