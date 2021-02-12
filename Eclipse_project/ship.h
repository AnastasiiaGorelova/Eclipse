#ifndef SHIP_H
#define SHIP_H

#include <QGraphicsPixmapItem>

class Ship : public QGraphicsPixmapItem{
public:
    Ship(int scene_w);

    // QGraphicsItem interface
public:
    void advance(int phase);

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    int shipSpeed = 0;
};

#endif // SHIP_H
