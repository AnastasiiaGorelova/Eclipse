#ifndef MAIN_GAME_GAME_FWD_H
#define MAIN_GAME_GAME_FWD_H

namespace eclipse {
    struct Game;
    static const int kWidth = 800;
    static const int kHeight = 600;
    enum GameState { kOngoing,
                     kFinished };
    enum FieldState { kAsteroid,
                      kLife,
                      kSpaceShip,
                      kShot,
                      kNothing };
    enum MoveDirection { kLeft,
                         kRight,
                         kNoMove };
    enum ObjectState { kAlive,
                       kDead };
    enum Controllers { Key,
                       Arduino };
    enum Actions { Delete_object,
                   Create_ship,
                   Create_shot,
                   Create_asteroid,
                   Move_object,
                   Finish_game,
                   Decrease_lives };

}// namespace eclipse

#endif// MAIN_GAME_GAME_FWD_H
