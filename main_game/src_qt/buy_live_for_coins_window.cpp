//
// Created by alena on 04.05.2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_buy_live_for_coins_window.h" resolved

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "buy_live_for_coins_window.h"
#include "ui_buy_live_for_coins_window.h"
#include <God.h>

extern God damn;

buy_live_for_coins_window::buy_live_for_coins_window(QWidget *parent) :
        QWidget(parent), ui(new Ui::buy_live_for_coins_window) {
    ui->setupUi(this);

    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                    (*this).size(),
                                    qApp->desktop()->availableGeometry()));


    QPixmap backgroung("../../images/menu_background.png"); //поменять картинку
    backgroung = backgroung.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, backgroung);
    this->setPalette(palette);

    setWindowTitle("Additional life");
    setFixedSize(400, 300);
}

buy_live_for_coins_window::~buy_live_for_coins_window() {
    delete ui;
}

void buy_live_for_coins_window::_on_yes_button_clicked() {
    damn.add_life_and_restart_game();
    close();
}

void buy_live_for_coins_window::_on_no_button_clicked() {
    damn.finish_game();
    close();
}

void buy_live_for_coins_window::buy_for_n_coins(int n) {
    auto *vlay = new QVBoxLayout(this);
    vlay->setAlignment(Qt::AlignCenter);

    QFont font;
    font.setWeight(QFont::ExtraBold); // set font weight with enum QFont::Weight
    font.setPixelSize(30); // this for setting font size

    QString line = QString::fromStdString("Купить\n дополнительную жизнь\n за " + std::to_string(n) + " монет?\n");
    auto text = new QLabel(line);
    text->setStyleSheet("background-color: rgba(0,0,0,0%); color : white;");
    text->setFont(font);
    text->setAlignment(Qt::AlignCenter);
    vlay -> addWidget(text);

    yes_button = new QPushButton("Да");
    yes_button->setStyleSheet(
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
    vlay->addWidget(yes_button);

    no_button = new QPushButton("Нет");
    no_button->setStyleSheet(
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
    vlay->addWidget(no_button);

    connect(no_button, &QPushButton::released, this, &buy_live_for_coins_window::_on_no_button_clicked);
    connect(yes_button, &QPushButton::released, this, &buy_live_for_coins_window::_on_yes_button_clicked);

    vlay->setAlignment(Qt::AlignCenter);
    this->setLayout(vlay);
}
