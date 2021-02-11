#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>

#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Shot : public QGraphicsPixmapItem{
public:
    Shot(QPointF initPosm, QGraphicsItem* parent);
private:
    int shotSpeed;

    // QGraphicsItem interface
public:
    virtual void advance(int phase);
};

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

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void OnGenerate();
private:
    Ui::Widget *ui;
    QGraphicsScene* scene;
    QTimer* animation;
    QTimer* generator;

};

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
#endif // WIDGET_H
