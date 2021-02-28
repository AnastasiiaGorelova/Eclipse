#ifndef MAIN_GAME_GAME_FWD_H
#define MAIN_GAME_GAME_FWD_H

namespace eclipse {
    struct Game;
    static const int kHeight = 10;
    static const int kWidth = 50;
    enum GameState { kOngoing,
                      kFinished };
    enum FieldState { kAsteroid,
                       kLife,
                       kSpaceShip,
                       kShot,
                       kNothing };
    enum MoveDirection {
        kLeft,
        kRight,
        kNoMove
    };
    enum ObjectState { kAlive,
                        kDead };

}// namespace eclipse

#endif//MAIN_GAME_GAME_FWD_H
