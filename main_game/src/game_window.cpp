
#include "../include/game_window.h"
#include "ui_game_window.h"

extern God damn;

game_window::game_window(QWidget *parent) :
        QWidget(parent), ui(new Ui::game_window) {
    ui->setupUi(this);
    QPixmap pix("../../images/cat.jpg");
    ui->label->setPixmap(pix.scaled(800, 600));
}

game_window::~game_window() {
    delete ui;
}

void game_window::show_menu_first(size_t width_, size_t height_) {
    width = width_;
    height = height_;
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

void game_window::start() {
    main_view.make_field(width, height);
    hide();
    main_view.show();
}

void game_window::stop_game() {
    main_view.scene->destroyed();
    main_view.close();
    this->show();
}



