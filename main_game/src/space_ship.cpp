#include "space_ship.h"
#include "game.h"
#include <utility>

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
    }// namespace
    std::pair<int, int> SpaceShip::find_ship() const {
        return {SpaceShip::x, SpaceShip::y};
    }
    int SpaceShip::get_size() const { return SpaceShip::size; }

    void SpaceShip::move(MoveDirection direction = kNoMove) {
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

}// namespace eclipse