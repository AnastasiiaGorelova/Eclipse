#include "asteroids.h"

namespace eclipse {
ObjectState Asteroid::get_state() const {
    return state;
}
std::string Asteroid::get_id() const {
    return id;
}
void Asteroid::move(int speed) {
    y += speed;
}
std::pair<int, int> Asteroid::get_coordinates() const {
    return {x, y};
}
int Asteroid::get_size() const {
    return size;
}
void Asteroid::destroy() {
    --lives;
    if (!lives) {
        state = kDead;
    }
}
}  // namespace eclipse