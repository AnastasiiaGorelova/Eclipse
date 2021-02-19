

// You may need to build the project (run Qt uic code generator) to get "ui_game_window.h" resolved

#include "../include/game_window.h"
#include "ui_game_window.h"

extern eclipse::Game *game;

game_window::game_window(QWidget *parent) :
        QWidget(parent), ui(new Ui::game_window) {
    ui->setupUi(this);
    QPixmap pix("../../images/cat.jpg");
    ui->label->setPixmap(pix.scaled(800, 600));
}

game_window::~game_window() {
    delete ui;
}

void game_window::on_start_clicked() {
    game = new eclipse::Game();
    game->makeGame(eclipse::WIDTH, eclipse::HEIGHT);
    hide();
}

void game_window::on_exit_clicked() {
    QApplication::quit();
}
