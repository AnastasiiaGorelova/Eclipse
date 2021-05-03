
#include "Selection.h"
#include <God.h>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include "ui_Selection.h"

extern God damn;

Selection::Selection(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Selection) {
    ui->setupUi(this);

    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                    (*this).size(),
                                    qApp->desktop()->availableGeometry()));

    //установка фона
    ui->setupUi(this);
    QPixmap backgroung("../../images/menu_background.png");  //поменять картинку
    backgroung = backgroung.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, backgroung);
    this->setPalette(palette);

    //установка кнопок и текста
    auto *wdg = new QWidget(this);
    auto *vlay = new QVBoxLayout(wdg);

    QFont font;
    font.setWeight(
        QFont::ExtraBold);  // set font weight with enum QFont::Weight
    font.setPixelSize(35);  // this for setting font size

    auto text = new QLabel("Выберете\n тип управления\n");
    text->setStyleSheet("background-color: rgba(0,0,0,0%); color : white;");
    text->setFont(font);
    text->setAlignment(Qt::AlignCenter);
    vlay->addWidget(text);

    key = new QPushButton("Клавиатура");
    key->setStyleSheet(
        "QPushButton{border: 1px solid transparent;text-align: center;"
        "color:rgba(255,255,255,255);"
        "border-radius: 8px;"
        "border-width: 3px;"
        "border-image: 9,2,5,2; "
        "background-position: top left;"
        "background-origin: content;"
        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
        "stop:0 rgba(200, 110, 100, 200), stop:1 rgba(130, 148, 130, 200));}"
        "QPushButton::chunk {background-color: qlineargradient(x1: 0, y1: 0, "
        "x2: 0, y2: 1, stop: 0 rgba(255,200,0,255), stop: 1 "
        "rgba(255,0,0,255));}"
        "QPushButton{border-color:qlineargradient(spread:pad, x1:0, y1:0, "
        "x2:1, y2:1, stop:0 rgba(255, 200, 200, 200), stop:1 rgba(255, 200, "
        "200, 200));}");
    vlay->addWidget(key);
    ard = new QPushButton("Arduino");
    ard->setStyleSheet(
        "QPushButton{border: 1px solid transparent;text-align: center;"
        "color:rgba(255,255,255,255);"
        "border-radius: 8px;"
        "border-width: 3px;"
        "border-image: 9,2,5,2; "
        "background-position: top left;"
        "background-origin: content;"
        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
        "stop:0 rgba(200, 110, 100, 200), stop:1 rgba(130, 148, 130, 200));}"
        "QPushButton::chunk {background-color: qlineargradient(x1: 0, y1: 0, "
        "x2: 0, y2: 1, stop: 0 rgba(255,200,0,255), stop: 1 "
        "rgba(255,0,0,255));}"
        "QPushButton{border-color:qlineargradient(spread:pad, x1:0, y1:0, "
        "x2:1, y2:1, stop:0 rgba(255, 200, 200, 200), stop:1 rgba(255, 200, "
        "200, 200));}");
    vlay->addWidget(ard);

    vlay->setAlignment(Qt::AlignCenter);
    wdg->setLayout(vlay);
    setCentralWidget(wdg);

    connect(key, &QPushButton::released, this, &Selection::_on_key_clicked);
    connect(ard, &QPushButton::released, this, &Selection::_on_ard_clicked);

    setWindowTitle("Set Controller");
    setFixedSize(400, 300);
}

Selection::~Selection() {
    delete ui;
}

void Selection::_on_key_clicked() {
    damn.select_game_controller(eclipse::Key);
    this->close();
}

void Selection::_on_ard_clicked() {
    damn.select_game_controller(eclipse::Arduino);
    this->close();
}
