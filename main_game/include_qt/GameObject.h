#ifndef MAIN_GAME_GAMEOBJECT_H
#define MAIN_GAME_GAMEOBJECT_H

#include "QObject"
#include "QGraphicsPixmapItem"

struct GameObject :  public QObject, public QGraphicsPixmapItem {

};

#endif //MAIN_GAME_GAMEOBJECT_H
