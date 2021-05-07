
#ifndef MAIN_GAME_KEY_CONTROLLER__H
#define MAIN_GAME_KEY_CONTROLLER__H

#include <QObject>
#include <QEvent>
#include <QKeyEvent>

#include "Modification_store.h"

class God;

struct Key_Controller : QObject {
    God* damn;
    void set_God(God* damn_);

    explicit Key_Controller(QObject *parent = nullptr);
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif //MAIN_GAME_KEY_CONTROLLER__H
