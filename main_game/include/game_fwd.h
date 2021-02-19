
#ifndef MAIN_GAME_GAME_FWD_H
#define MAIN_GAME_GAME_FWD_H

namespace eclipse {
    struct Game;
    static const int HEIGHT = 10;
    static const int WIDTH = 50;
    enum Game_state { ONGOING,
                      FINISHED };
    enum Field_state { ASTEROID,
                       LIFE,
                       SPACE_SHIP,
                       SHOT,
                       NOTHING };
    enum Go {
        LEFT,
        RIGHT,
        NO_MOVE
    };
    enum Object_state { ALIVE,
                        DEAD };

}// namespace eclipse

#endif//MAIN_GAME_GAME_FWD_H
