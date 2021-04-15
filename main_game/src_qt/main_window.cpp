#include "main_window.h"
#include <QDesktopWidget>
#include <QGraphicsProxyWidget>
#include <QKeyEvent>
#include <QStyle>
#include "God.h"
#include "ui_main_window.h"

extern God damn;

main_window::main_window(QWidget *parent)
    : QWidget(parent), ui(new Ui::main_window) {
    ui->setupUi(this);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                    (*this).size(),
                                    qApp->desktop()->availableGeometry()));
}

main_window::~main_window() {
    delete ui;
}

void main_window::make_field() {
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, width, height);
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QBrush(QImage("../../images/background.jpeg")));
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFrameShape(QFrame::NoFrame);

    scene_info = new QGraphicsScene();
    scene_info->setSceneRect(0, 0, width, 30);
    ui->graphicsView_2->setScene(scene_info);
    scene_info->setBackgroundBrush(Qt::black);
    ui->graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setFrameShape(QFrame::NoFrame);

    setFixedSize(800, 630);
    setWindowTitle("Eclipse");
}

void main_window::set(int x,
                      int y,
                      int size,
                      const std::string &hash,
                      const std::string &object_name) {
    auto *object = new GameObject();
    QString filename =
        "../../images/" + QString::fromStdString(object_name) + ".png";
    object->setPixmap(QPixmap(filename).scaled(size, size));
    object->setPos(x, y);
    scene->addItem(object);
    hash_table[hash] = object;
}

void main_window::move(int x, int y, const std::string &hash) {
    if (hash_table[hash] != nullptr){
        hash_table[hash]->setPos(x, y);
    }
}

void main_window::delete_obj(const std::string &hash) {
    if (hash_table[hash] != nullptr) {
        hash_table[hash]->del();
        hash_table[hash] = nullptr;
    }

}

void main_window::set_timer() {
    time = new QLabel("Time:");
    time-> setStyleSheet("background-color: black; color : white;");
    number_for_time = new QLabel("00:00");
    number_for_time -> setStyleSheet("background-color: black; color : white;");

    auto *item_1 = new QGraphicsRectItem;
    item_1->setRect(QRect(0, 0, 80, 30));
    scene_info->addItem(item_1);
    auto *pMyProxy_1 = new QGraphicsProxyWidget(item_1);
    pMyProxy_1->setWidget(time);
    pMyProxy_1->setPos(10, 7);

    auto *item_2 = new QGraphicsRectItem;
    item_2->setRect(QRect(0, 0, 80, 30));
    scene_info->addItem(item_2);
    auto *pMyProxy_2 = new QGraphicsProxyWidget(item_2);
    pMyProxy_2->setWidget(number_for_time);
    pMyProxy_2->setPos(60, 7);
}

void main_window::set_lives() {
    auto img_heart = QPixmap("../../images/heart.png").scaled(25, 25);
    auto *object_1 = new GameObject();
    object_1->setPixmap(img_heart);
    scene_info->addItem(object_1);
    object_1->setPos(700, 3.5);
    hash_table["heart_1"] = object_1;

    auto *object_2 = new GameObject();
    object_2->setPixmap(img_heart);
    object_2->setPos(730, 3.5);
    scene_info->addItem(object_2);
    hash_table["heart_2"] = object_2;

    auto *object_3 = new GameObject();
    object_3->setPixmap(img_heart);
    object_3->setPos(760, 3.5);
    scene_info->addItem(object_3);
    hash_table["heart_3"] = object_3;
}

void main_window::decrease_lives() {
    if (hash_table.find("heart_1") != hash_table.end()) {
        hash_table["heart_1"]->del();
        hash_table.erase("heart_1");
    } else if (hash_table.find("heart_2") != hash_table.end()) {
        hash_table["heart_2"]->del();
        hash_table.erase("heart_2");
    } else if (hash_table.find("heart_3") != hash_table.end()) {
        hash_table["heart_3"]->del();
        hash_table.erase("heart_3");
    }
}

void main_window::change_timer() {
    cur_time++;
    auto [min, sec] = find_time_string(cur_time);
    QString time_string =
            QString::fromStdString(min) + ":" + QString::fromStdString(sec);
    number_for_time -> setText(time_string);
}

std::pair<std::string, std::string> main_window::find_time_string(int x) {
    std::string min = std::to_string(x / 60);
    if (min.size() == 0) {
        min = "00";
    }
    if (min.size() == 1) {
        min = "0" + min;
    }
    std::string sec = std::to_string(x % 60);
    if (sec.size() == 0) {
        min = "00";
    }
    if (sec.size() == 1) {
        sec = "0" + sec;
    }
    return std::pair<std::string, std::string>(min, sec);
}

void main_window::start_timer() {
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(change_timer()));
    timer->start(1000);
}

