
#ifndef MAIN_GAME_KEY_CONTROLLER__H
#define MAIN_GAME_KEY_CONTROLLER__H

#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include "controllers_in.h"

class God;

struct Key_Controller : QObject, virtual Controller_in {
    void set_God(God* damn_) override;

    explicit Key_Controller(QObject *parent = nullptr);
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif //MAIN_GAME_KEY_CONTROLLER__H
