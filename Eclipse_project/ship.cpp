#include "ship.h"
#include "shots.h"
#include <QKeyEvent>
#include <QGraphicsScene>

Ship::Ship(int scene_w)  : QGraphicsPixmapItem(0) {
    setPixmap(QPixmap("://SpaceShip.png").scaled(130, 130));
    setPos(0, scene_w - pixmap().height()); //делаем так, чтобы кораль стал ровно по нижнему краю окна
    setFlag(QGraphicsItem::ItemIsFocusable); //элемент может получить фокус, т.е. теперь мы можем им управять с клавиатуры, наша программа настроена на корабль и только
    setFocus();
}

void Ship::advance(int phase){
    if (phase) {
        moveBy(shipSpeed, 0);
    }
}

void Ship::keyPressEvent(QKeyEvent *event){ //событие: нажали кнопку
    switch (event->key()){ //возвращает код нажатой клавиши
    case Qt::Key_Left:
        shipSpeed = -6; //двигаем влево, корабль смещается относительно своих координат
        break;
    case Qt::Key_Right:
        shipSpeed = 6;
        break;
    case Qt::Key_Space:
        scene()->addItem(new Shot(QPointF(mapToScene(pixmap().width()/2 - 8, 0)), 0)); //fix it! костыль, изображение не симметричное
                                                //поменяли родителя, иначе пуля будет кататься вслед за самолетом уже после вылета
                                               //ьеперь родитель - сцена, из-за того, что фактический родитель - 0 (последний ноль в строке), надо добалять элемент на сцену ручками (сделано в начале строки)
        break;
    default:
        break;
    }
}

void Ship::keyReleaseEvent(QKeyEvent *event){ //событие: отпустили кнопку
    switch (event->key()){ //возвращает код отпущенной клавиши
    case Qt::Key_Left:
        shipSpeed = 0; //останавливаем корабль
        break;
    case Qt::Key_Right:
        shipSpeed = 0;
        break;
    default:
        break;
    }
}
