
#include "include/main_window.h"
#include "ui_main_window.h"
#include "../include/asteroids_qt.h"

main_window::main_window(QWidget *parent) :
        QWidget(parent), ui(new Ui::main_window) {
    ui->setupUi(this);
}

main_window::~main_window() {
    delete ui;
}

void main_window::make_field(int width, int height) {
    scene = new QGraphicsScene();
    scene -> setSceneRect(0, 0, width, height);
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QBrush(QImage("../../images/background.jpeg")));
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(width, height);
    setWindowTitle("Eclipse");
    resize(width, height);
}

void main_window::set(int x, int y, int size, const std::string& hash) {
    auto* object = new Asteroids_qt();
    object->setPixmap(QPixmap("../../images/SpaceShip.png").scaled(size, size));
    object->setPos(x, y);
    scene->addItem(object);
    hash_table[hash] = object;
}

void main_window::move(int x, int y, const std::string& hash) {
    hash_table[hash]->setPos(x, y);
}

void main_window::end_game() {
    scene->destroyed();
    hide();
}

