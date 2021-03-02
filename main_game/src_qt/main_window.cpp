#include "include_qt/main_window.h"
#include "ui_main_window.h"
#include "include_qt/God.h"
#include <QKeyEvent>
#include <QStyle>
#include <QDesktopWidget>

extern God damn;

main_window::main_window(QWidget *parent) :
        QWidget(parent), ui(new Ui::main_window) {
    ui->setupUi(this);
    qApp->installEventFilter(this);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, (*this).size(), qApp->desktop()->availableGeometry()));
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

    scene_info = new QGraphicsScene();
    scene_info->setSceneRect(0, 0, width, height);
    ui->graphicsView_2->setScene(scene_info);
    //scene_info->setBackgroundBrush(Qt::black);
    ui->graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);
    setWindowTitle("Eclipse");
}

void main_window::set(int x, int y, int size, const std::string& hash, const std::string &object_name) {
    auto* object = new GameObject();
    QString filename = "../../images/"+ QString::fromStdString(object_name) + ".png";
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

void main_window::set_timer() {

}

void main_window::set_lives() {
    auto* object_1 = new GameObject();
    object_1->setPixmap(QPixmap("../../images/heart.png").scaled(25, 25));
    object_1->setPos(0, 0);
    scene_info->addItem(object_1);
    hash_table["heart_1"] = object_1;

    auto* object_2 = new GameObject();
    object_2->setPixmap(QPixmap("../../images/heart.png").scaled(25, 25));
    object_2->setPos(745, 3.5);
    scene_info->addItem(object_2);
    hash_table["heart_2"] = object_2;

    auto* object_3 = new GameObject();
    object_3->setPixmap(QPixmap("../../images/heart.png").scaled(25, 25));
    object_3->setPos(715, 3.5);
    scene_info->addItem(object_3);
    hash_table["heart_3"] = object_3;
}



