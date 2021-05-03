#ifndef MAIN_GAME_CHANGES_H
#define MAIN_GAME_CHANGES_H

namespace eclipse {
    struct Changes {
        Actions action;
        std::string id = "-";
        std::pair<int, int> new_coordinates = {-1, -1};
        int size = 0;
    };
}// namespace eclipse

#endif//MAIN_GAME_CHANGES_H
