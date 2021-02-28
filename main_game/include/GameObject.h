#ifndef MAIN_GAME_GAMEOBJECT_H
#define MAIN_GAME_GAMEOBJECT_H

#include "QObject"
#include "QGraphicsPixmapItem"
#include <QKeyEvent>
#include "God.h"

struct GameObject :  public QObject, public QGraphicsPixmapItem {

};

#endif //MAIN_GAME_GAMEOBJECT_H
