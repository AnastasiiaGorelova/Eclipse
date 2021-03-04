#include "space_ship.h"
#include <string>
#include <utility>
#include "game.h"

namespace eclipse {
namespace {
void moving(int &x, int vec, int size = 0) {
    if (x + vec >= kWidth - size) {
        x = kWidth - size;
    } else if (x + vec <= 0) {
        x = 0;
    } else {
        x += vec;
    }
}
}  // namespace

std::pair<int, int> spaceship::get_coordinates() const {
    return {spaceship::x, spaceship::y};
}

int spaceship::get_size() const {
    return spaceship::size;
}

std::string spaceship::get_id() const {
    return id;
}

void spaceship::move(MoveDirection direction = kNoMove) {
    switch (direction) {
        case kLeft:
            moving(x, -speed);
            break;
        case kRight:
            moving(x, speed, size);
            break;
        case kNoMove:
            return;
    }
}

}  // namespace eclipse