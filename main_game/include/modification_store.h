#ifndef MAIN_GAME_MODIFICATION_STORE_H
#define MAIN_GAME_MODIFICATION_STORE_H

#include <vector>
#include <mutex>
#include "game_fwd.h"

struct Modification_store {
    eclipse::MoveDirection get_aggregated_changes();

    void pushed_button_left();
    void pushed_button_right();
    void pushed_pause_or_play();

private:
    std::vector<eclipse::MoveDirection> modifications;

    std::mutex mod_mx;
};

#endif  // MAIN_GAME_MODIFICATION_STORE_H
