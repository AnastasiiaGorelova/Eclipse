
#ifndef MAIN_GAME_SPACE_SHIP_H
#define MAIN_GAME_SPACE_SHIP_H

#include "game_fwd.h"
#include <utility>

#include <QGraphicsPixmapItem>

namespace eclipse {
    struct Space_ship : public QObject, public QGraphicsPixmapItem {
    private:
        Q_OBJECT

    public:
         const int size = 150;// TODO: the exact coordinates
        int x = WIDTH / 2 - size/2; // central coordinates
        int y = HEIGHT - size - 20;
        explicit Space_ship(QGraphicsItem *parent = 0);
        void shoot() {}

        std::pair<int, int> where_is_ship() const;//x,y coordinates

         int get_size() const;

        void set_ship(int const width, int const height, int const size_of_ship);
    };
}// namespace eclipse

#endif//MAIN_GAME_SPACE_SHIP_H
