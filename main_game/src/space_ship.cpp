
#include "../include/space_ship.h"
#include <utility>
#include "../include/game.h"


extern eclipse::Game *game;

namespace eclipse {
    std::pair<int, int> Space_ship::where_is_ship() const {
        return std::make_pair(Space_ship::x, Space_ship::y);
    }
    int Space_ship::get_size() const { return Space_ship::size; }


    //for qt
    void Space_ship::set_ship(const int width, const int height, int const size_of_ship) {
        setPixmap(QPixmap("../../images/SpaceShip.png").scaled(size_of_ship, size_of_ship));
        setPos(width, height); //поменять начало отсчета
        game->scene->addItem(this);
    }

    Space_ship::Space_ship(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {}


}// namespace eclipse