#ifndef SHOTS_H
#define SHOTS_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class Shot : public QGraphicsPixmapItem{
public:
    Shot(QPointF initPosm, QGraphicsItem* parent);
private:
    int shotSpeed;

     //QGraphicsItem interface;
public:
    virtual void advance(int phase);
};

#endif // SHOTS_H
