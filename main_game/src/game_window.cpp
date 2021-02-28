#include "../include/game_window.h"
#include "ui_game_window.h"
#include "../include/main_window.h"
#include "ui_main_window.h"
#include "../include/God.h"


game_window::game_window(QWidget *parent) :
        QWidget(parent), ui(new Ui::game_window) {
    ui->setupUi(this);
    QPixmap pix("../../images/cat.jpg");
    ui->label->setPixmap(pix.scaled(800, 600));

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



