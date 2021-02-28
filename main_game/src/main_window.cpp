#include "include/main_window.h"
#include "ui_main_window.h"
#include "../include/God.h"
#include <iostream>
#include <string>

extern God damn;

main_window::main_window(QWidget *parent) :
        QWidget(parent), ui(new Ui::main_window) {
    ui->setupUi(this);
    qApp->installEventFilter(this);
}

main_window::~main_window() {
    delete ui;
}

void main_window::make_field() {
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, width, height);
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QBrush(QImage("../../images/background.jpeg")));
    scene->setStickyFocus(true);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);
    setWindowTitle("Eclipse");
}

void main_window::set(int x, int y, int size, const std::string& hash, const std::string &object_name) {
    auto* object = new GameObject();
    QString filename = "../../images/"+ QString::fromStdString(object_name) + ".png";

    std::cout << "../../images/"+ object_name + ".png" << std::endl;;
    object->setPixmap(QPixmap(filename).scaled(size, size));
    object->setPos(x, y);
    scene->addItem(object);
    hash_table[hash] = object;
}

void main_window::move(int x, int y, const std::string& hash) {
    hash_table[hash]->setPos(x, y);
}

void main_window::delete_obj(const std::string& hash) {
    delete hash_table[hash];
    hash_table.erase(hash);
}

bool main_window::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress){
        auto *keyEvent = dynamic_cast<QKeyEvent *>(event);
        switch (keyEvent->key()){
            case Qt::Key_Left:
                God::pushed_button_left();
                break;
            case Qt::Key_Right:
                God::pushed_button_right();
                break;
            default:
                break;
        }
    }
    return QObject::eventFilter(obj, event);
}



