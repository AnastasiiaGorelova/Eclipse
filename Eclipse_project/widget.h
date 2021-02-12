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
    QGraphicsScene *scene;
    QTimer *animation;
    QTimer *generator;

};

#endif // WIDGET_H
