#include "asteroids.h"

Asteroids::Asteroids(int x) : QGraphicsPixmapItem(0) { //вызываем конструктор родительского класса
    int p = rand()%130;
    while(p < 90){
        p = rand()%130;
    }
    setPixmap(QPixmap("://RegularAsteroid.png").scaled(p, p));
    setPos(rand()%(x - pixmap().width()), 0); //смещение системы координат
}

void Asteroids::advance(int phase){
    if (phase) {
        moveBy(0, speed); //смещение относительно ранего состоятния объекта, т.е. хотим оставить сост по x и сместить на 2 по y.
        if (data(0).toBool()){
            delete this;
        }
    }
}

int Asteroids::type() const{ //необходимо, для того, чтобы проверить тип графического элемента, (например, появится меню, чтобы мы случайно его не убили пулей:)
    return Type;
}
