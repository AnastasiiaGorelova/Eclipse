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
    void Shot::move_for_alien() {
        y += speed;
    }
    bool operator<(const Shot &first, const Shot &second) {
        return first.y < second.y;
    }
}// namespace eclipse