#include "monster.h"

namespace eclipse {

    std::pair<int, int> monster::get_coordinates() const {
        return {x, y};
    }

    std::string monster::get_id() const {
        return id;
    }

    int monster::get_size() const {
        return size;
    }

    void monster::move(MoveDirection direction) {
        //TODO
    }

    MonsterState monster::get_state() const {
        return state;
    }

    void monster::change_state(MonsterState new_state) {
        state = new_state;
    }
}// namespace eclipse