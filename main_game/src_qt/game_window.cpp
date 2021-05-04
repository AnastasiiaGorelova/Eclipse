#include <God.h>
#include <game_window.h>
#include <QDesktopWidget>
#include <QLineEdit>
#include <QStyle>
#include "ui_game_window.h"

extern God damn;

game_window::game_window(QWidget *parent)
    : QWidget(parent), ui(new Ui::game_window) {
    ui->setupUi(this);
    QPixmap pix("../../images/main.jpg");
    ui->label->setPixmap(pix.scaled(800, 630));
    ui->start->setStyleSheet(
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
    ui->exit->setStyleSheet(
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

    ui->Eclipse->setText("Eclipse");
    ui->Eclipse->setStyleSheet(
        "background-color: rgba(0,0,0,0%); color : white;");
    QFont font;
    font.setWeight(QFont::ExtraBold);
    font.setPixelSize(120);
    ui->Eclipse->setFont(font);
    ui->Eclipse->setAlignment(Qt::AlignCenter);

    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                    (*this).size(),
                                    qApp->desktop()->availableGeometry()));
}

game_window::~game_window() {
    delete ui;
}

void game_window::show_menu_first() {
    resize(width, height);
    setWindowTitle("Eclipse");
    show();
}

void game_window::on_start_clicked() {
    damn.clicked_on_start();
}

void game_window::on_exit_clicked() {
    damn.clicked_on_exit();
}
