
#ifndef MAIN_GAME_ASTEROIDS_QT_H
#define MAIN_GAME_ASTEROIDS_QT_H

#include "QObject"
#include "QGraphicsPixmapItem"
#include "asteroids_presentation.h"
#include "game.h"


extern eclipse::Game *game;

namespace eclipse {

struct Asteroids_qt : public QObject, public QGraphicsPixmapItem, Asteroids_presentation {
    void set_asteroid(int x, int y, int size) override;
};

}

#endif //MAIN_GAME_ASTEROIDS_QT_H
