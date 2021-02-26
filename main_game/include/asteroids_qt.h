
#ifndef MAIN_GAME_ASTEROIDS_QT_H
#define MAIN_GAME_ASTEROIDS_QT_H

#include "QObject"
#include "QGraphicsPixmapItem"

struct Asteroids_qt : public QObject, public QGraphicsPixmapItem {
    void set_asteroid(int x, int y, int size);
};



#endif //MAIN_GAME_ASTEROIDS_QT_H
