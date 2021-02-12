#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <QGraphicsPixmapItem>

class Asteroids : public QGraphicsPixmapItem {
public:
    enum {
        Type = UserType +1
    };
    Asteroids (int x); //ширина сцены

    virtual void advance(int phase); //переопределим для себя этот метод

    virtual int type() const;

private:
    int speed = 2;

};

#endif // ASTEROIDS_H
