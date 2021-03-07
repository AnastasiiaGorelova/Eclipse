#include "include_qt/main_window.h"
#include <QDesktopWidget>
#include <QGraphicsProxyWidget>
#include <QKeyEvent>
#include <QStyle>
#include "include_qt/God.h"
#include "ui_main_window.h"

extern God damn;

main_window::main_window(QWidget *parent)
    : QWidget(parent), ui(new Ui::main_window) {
    ui->setupUi(this);
    qApp->installEventFilter(this);
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

bool main_window::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        auto *keyEvent = dynamic_cast<QKeyEvent *>(event);
        switch (keyEvent->key()) {
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
    return QObject::eventFilter(obj, event);
}

void main_window::set_timer() {
    time = new QLabel("Time:");
    number_for_time = new QLabel("00:00");

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
    auto *object_1 = new GameObject();
    object_1->setPixmap(QPixmap("../../images/heart.png").scaled(25, 25));
    scene_info->addItem(object_1);
    object_1->setPos(760, 3.5);
    hash_table["heart_1"] = object_1;

    auto *object_2 = new GameObject();
    object_2->setPixmap(QPixmap("../../images/heart.png").scaled(25, 25));
    object_2->setPos(730, 3.5);
    scene_info->addItem(object_2);
    hash_table["heart_2"] = object_2;

    auto *object_3 = new GameObject();
    object_3->setPixmap(QPixmap("../../images/heart.png").scaled(25, 25));
    object_3->setPos(700, 3.5);
    scene_info->addItem(object_3);
    hash_table["heart_3"] = object_3;
}
