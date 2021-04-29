#include "Modification_store.h"
#include <God.h>

extern God damn;

void Modification_store::pushed_button_left() {
    modifications.push_back(eclipse::kLeft);
}

void Modification_store::pushed_button_right() {
    modifications.push_back(eclipse::kRight);
}

std::pair<eclipse::MoveDirection, int> Modification_store::give_changes() {
    int all_right = 0;
    int all_left = 0;
    for (eclipse::MoveDirection x : modifications) {
        switch (x) {
            case eclipse::kRight:
                all_right++;
                break;
            case eclipse::kLeft:
                all_left++;
                break;
            default:
                break;
        }
    }
    modifications.clear();
    int result = all_right - all_left;
    if (result == 0) {
        return std::make_pair(eclipse::kNoMove, 0);
    }
    if (result > 0) {
        return std::make_pair(eclipse::kRight, result);
    }
    if (result < 0) {
        return std::make_pair(eclipse::kLeft, result);
    }
}
