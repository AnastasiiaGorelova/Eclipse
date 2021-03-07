#include "shots.h"

namespace eclipse {
    std::pair<int, int> Shot::get_coordinates() const {
        return {x, y};
    }
    std::string Shot::get_id() const {
        return id;
    }
    int Shot::get_size() const {
        return size;
    }
    void Shot::move() {
        y -= speed;
    }
}// namespace eclipse