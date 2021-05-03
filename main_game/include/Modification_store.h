#ifndef MAIN_GAME_MODIFICATION_STORE_H
#define MAIN_GAME_MODIFICATION_STORE_H

#include <vector>
#include "game_fwd.h"

struct Modification_store {
    void pushed_button_left();
    void pushed_button_right();

    std::pair<eclipse::MoveDirection, int> give_changes();

private:
    std::vector<eclipse::MoveDirection> modifications;
};

#endif  // MAIN_GAME_MODIFICATION_STORE_H
