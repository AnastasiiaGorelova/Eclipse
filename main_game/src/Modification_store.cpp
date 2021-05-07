#include "Modification_store.h"
#include <God.h>

extern God damn;

void Modification_store::pushed_button_left() {
    modifications.push_back(eclipse::kLeft);
}

void Modification_store::pushed_button_right() {
    modifications.push_back(eclipse::kRight);
}

eclipse::MoveDirection Modification_store::give_changes() {
    int all_right = 0;
    int all_left = 0;
    for (auto x : modifications) {
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
        return eclipse::kNoMove;
    }
    if (result > 0) {
        return eclipse::kRight;
    }
    if (result < 0) {
        return eclipse::kLeft;
    }
}
