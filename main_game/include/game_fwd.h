
#ifndef MAIN_GAME_GAME_FWD_H
#define MAIN_GAME_GAME_FWD_H

namespace eclipse {
    struct Game;
    static const int D_HEIGHT = 10;
    static const int D_WIDTH = 50;

    static const int HEIGHT = 600;
    static const int WIDTH = 800;


    enum Game_state { ONGOING,
                      FINISHED };
    enum Field_state { ASTEROID,
                       LIFE,
                       SPACE_SHIP,
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
