#include "bonus.h"

namespace eclipse {
    void Bonus::move(int speed) {
        y += speed;
    }
    std::pair<int, int> Bonus::get_coordinates() const {// x,y coordinates
        return {x, y};
    }
    std::string Bonus::get_id() const {
        return id;
    }
    std::string Bonus::get_type() const {
        return type;
    }

    bool operator<(const Bonus &first, const Bonus &second) {
        return first.y > second.y;
    }
}// namespace eclipse
