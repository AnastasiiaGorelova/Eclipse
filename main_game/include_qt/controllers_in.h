
#ifndef MAIN_GAME_CONTROLLERS_IN_H
#define MAIN_GAME_CONTROLLERS_IN_H

class God;

class Controller_in {
public:
    God *damn;
    virtual void set_God(God *damn_) = 0;
};

#endif  // MAIN_GAME_CONTROLLERS_IN_H
