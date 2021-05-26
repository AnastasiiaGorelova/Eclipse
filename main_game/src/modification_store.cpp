#include "modification_store.h"
#include <god.h>

void Modification_store::pushed_button_left() {
    modifications.push_back(eclipse::kLeft);
}

void Modification_store::pushed_button_right() {
    modifications.push_back(eclipse::kRight);
}

void Modification_store::pushed_pause_or_play() {
    modifications.push_back(eclipse::kChangeGameState);
}

eclipse::MoveDirection Modification_store::get_aggregated_changes() {
    int all_right = 0;
    int all_left = 0;
    int is_stop = 0;
    for (auto x : modifications) {
        switch (x) {
            case eclipse::kRight:
                all_right++;
                break;
            case eclipse::kLeft:
                all_left++;
                break;
            case eclipse::kChangeGameState:
                is_stop = 1;
                break;
        }
    }
    modifications.clear();
    if (is_stop) {
        return eclipse::kChangeGameState;
    }
    int result = all_right - all_left;
    if (result == 0) {
        return eclipse::kNoMove;
    }
    if (result > 0) {
        return eclipse::kRight;
    }
    if (result < 0) {
        return eclipse::kLeft;
    }
}
