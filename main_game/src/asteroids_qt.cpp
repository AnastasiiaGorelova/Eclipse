
#include <include/asteroids_qt.h>

namespace eclipse{
    void Asteroids_qt::set_asteroid(int x, int y, int size) {
    setPixmap(QPixmap("../../images/RegularAsteroid.png").scaled(size, size));
    setPos(x, y); //поменять начало отсчета
    game->scene->addItem(this);
}
}

