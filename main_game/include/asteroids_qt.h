
#ifndef MAIN_GAME_ASTEROIDS_QT_H
#define MAIN_GAME_ASTEROIDS_QT_H

#include "QObject"
#include "QGraphicsPixmapItem"
#include "../include/God.h"

extern God damn;

struct GameObject : public QObject, public QGraphicsPixmapItem {
};



#endif //MAIN_GAME_ASTEROIDS_QT_H
