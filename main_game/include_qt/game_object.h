#ifndef MAIN_GAME_GAME_OBJECT_H
#define MAIN_GAME_GAME_OBJECT_H

#include "QGraphicsPixmapItem"
#include "QObject"

struct GameObject : public QObject, public QGraphicsPixmapItem {
    void del();
};

#endif  // MAIN_GAME_GAME_OBJECT_H
