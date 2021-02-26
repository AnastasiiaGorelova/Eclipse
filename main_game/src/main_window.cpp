//
// Created by alena on 20.02.2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_main_window.h" resolved

#include "main_window.h"
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

void main_window::set(int x, int y, int size, int hash, std::string name) {
    auto* ship = new eclipse::Asteroids_qt(); //todo new
    ship->setPixmap(QPixmap("../../images/SpaceShip.png").scaled(size, size));
    ship->setPos(x, y);
    scene->addItem(ship);
    hash_table[hash] = ship;
}

void main_window::move(int x, int y, int hash) {
    hash_table[hash]->setPos(x, y);
}

void main_window::end_game() {
    scene->destroyed();
    hide();
}

