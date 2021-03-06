#ifndef MAIN_GAME_GAMEOBJECT_H
#define MAIN_GAME_GAMEOBJECT_H

#include "QGraphicsPixmapItem"
#include "QObject"

struct GameObject : public QObject, public QGraphicsPixmapItem {};

#endif  // MAIN_GAME_GAMEOBJECT_H
