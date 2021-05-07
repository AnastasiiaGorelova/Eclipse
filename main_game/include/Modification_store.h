#ifndef MAIN_GAME_MODIFICATION_STORE_H
#define MAIN_GAME_MODIFICATION_STORE_H

#include <vector>
#include "game_fwd.h"

struct Modification_store {
    void pushed_button_left();
    void pushed_button_right();
    eclipse::MoveDirection get_aggregated_changes();

private:
    std::vector<eclipse::MoveDirection> modifications;
};

#endif  // MAIN_GAME_MODIFICATION_STORE_H
