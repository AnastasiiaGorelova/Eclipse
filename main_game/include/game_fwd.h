#ifndef MAIN_GAME_GAME_FWD_H
#define MAIN_GAME_GAME_FWD_H

#include <string>

namespace eclipse {
    struct Game;
    static const int kWidth = 800;
    static const int kHeight = 600;
    static const int alien_lives = 5;
    static const std::string default_id = "nothing";
    enum GameState { kOngoing,
                     kFinished };
    enum MoveDirection { kLeft,
                         kRight,
                         kNoMove,
                         kUp,
                         kDown,
                         kChangeGameState };
    enum ObjectState { kAlive,
                       kDead };

    enum Controllers { Key,
                       Arduino };
    enum Actions {
        Create_ship,
        Create_alien,
        Create_shot,
        Create_alien_shot,
        Create_asteroid,
        Create_coin,
        Create_heart,
        Create_alien_heart,
        Create_diamond,
        Move_object,
        Delete_object,
        Break_asteroid,
        Slow_down_game,
        Add_coin,
        Add_heart,
        Decrease_lives
    };

    enum MonsterState {
        Going_out,
        Leaving,
        On_the_field,
        Not_on_the_field
    };

}// namespace eclipse

#endif// MAIN_GAME_GAME_FWD_H
