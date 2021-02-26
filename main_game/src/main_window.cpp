
#include "include/main_window.h"
#include "ui_main_window.h"
#include "../include/game_window.h"

extern God damn;

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

void main_window::set(int x, int y, int size, const std::string& hash, const std::string &object_name) {
    QString filename = "../../image"+ QString::fromStdString(object_name) + "png";
    auto* object = new GameObject();
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

void main_window::keyPressEvent(QKeyEvent *event) {
    switch (event->key()){
        case Qt::Key_Left:
            damn.pushed_button_left();
            break;
        case Qt::Key_Right:
            damn.pushed_button_right();
            break;
        default:
            break;
    }
}


