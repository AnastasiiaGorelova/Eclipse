#include "bonus.h"

namespace eclipse {
    void Coin::move(int speed) {
        y += speed;
    }
    std::pair<int, int> Coin::get_coordinates() const {// x,y coordinates
        return {x, y};
    }
    std::string Coin::get_id() const {
        return id;
    }

    void Heart::move(int speed) {
        y += speed;
    }
    std::pair<int, int> Heart::get_coordinates() const {// x,y coordinates
        return {x, y};
    }
    std::string Heart::get_id() const {
        return id;
    }
}
