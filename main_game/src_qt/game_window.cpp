#include <include_qt/game_window.h>
#include "ui_game_window.h"
#include <include_qt/God.h>

game_window::game_window(QWidget *parent) :
        QWidget(parent), ui(new Ui::game_window) {
    ui->setupUi(this);
    QPixmap pix("../../images/bakcgroung_2.0.jpg");
    ui->label->setPixmap(pix.scaled(800, 600));
    ui->start->setStyleSheet("QPushButton{border: 1px solid transparent;text-align: center;"
                                  "color:rgba(255,255,255,255);"
                                  "border-radius: 8px;"
                                  "border-width: 3px;"
                                  "border-image: 9,2,5,2; "
                                  "background-position: top left;"
                                  "background-origin: content;"
                                  "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(200, 110, 100, 200), stop:1 rgba(130, 148, 130, 200));}"
                                  "QPushButton::chunk {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgba(255,200,0,255), stop: 1 rgba(255,0,0,255));}"
                                  "QPushButton{border-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 200, 200, 200), stop:1 rgba(255, 200, 200, 200));}"
    );
    ui->exit->setStyleSheet("QPushButton{border: 1px solid transparent;text-align: center;"
                            "color:rgba(255,255,255,255);"
                            "border-radius: 8px;"
                            "border-width: 3px;"
                            "border-image: 9,2,5,2; "
                            "background-position: top left;"
                            "background-origin: content;"
                            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(200, 110, 100, 200), stop:1 rgba(130, 148, 130, 200));}"
                            "QPushButton::chunk {background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgba(255,200,0,255), stop: 1 rgba(255,0,0,255));}"
                            "QPushButton{border-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 200, 200, 200), stop:1 rgba(255, 200, 200, 200));}"
    );
    ui->textEdit->setStyleSheet("QTextEdit { background-color: QColor(255, 255, 255, 0)}");
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
    God::clicked_on_start();
}

void game_window::on_exit_clicked() {
    God::clicked_on_exit();
}



