#ifndef MAIN_GAME_GAME_FWD_H
#define MAIN_GAME_GAME_FWD_H

#include <string>

namespace eclipse {
    struct Game;
    static const int kWidth = 800;
    static const int kHeight = 600;
    static const std::string default_id = "nothing";
    enum GameState { kOngoing,
                     kFinished };
    enum MoveDirection { kLeft,
                         kRight,
                         kNoMove };
    enum ObjectState { kAlive,
                       kDead };
    enum Controllers { Key,
                       Arduino };
    enum Actions {
        Create_ship,
        Create_shot,
        Create_asteroid,
        Move_object,
        Delete_object,
        Break_asteroid,
        Finish_game,
        Decrease_lives
    };

}// namespace eclipse

#endif// MAIN_GAME_GAME_FWD_H
