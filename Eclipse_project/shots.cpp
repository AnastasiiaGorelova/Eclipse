#include "shots.h"
#include "asteroids.h"

Shot::Shot(QPointF initPos, QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
    shotSpeed = 5;
    setPixmap(QPixmap("://FireShot.png"));
    setPos(initPos);
}

void Shot::advance(int phase) {
    if (!phase) {
        foreach(QGraphicsItem* item, collidingItems()){ //возращает список элементов, с которыми столкнулся нам элемент, проходимся по этому списку
            if (item->type() == Asteroids::Type){
            item->setData(0, true); //позволяется хранить ключ - значения об объекте
            //удалить астроид прямо здесь мы не можем, приведем к ошибке, удалять объекты можем в из advance
            setData(0, true);
            }
        }

    } else {
        moveBy(0, -shotSpeed);
        if (data(0).toBool()){
            delete this;
        }
    }
}
