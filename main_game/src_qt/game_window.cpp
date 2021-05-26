#include <god.h>
#include <game_window.h>
#include <QDesktopWidget>
#include <QStyle>
#include "ui_game_window.h"

#define window_width 800
#define window_height 630
#define point_size 120
#define local_leaderboard 0
#define server_leaderboard 1

game_window::game_window(QWidget *parent)
    : QWidget(parent), ui(new Ui::game_window) {
    ui->setupUi(this);

    QPixmap pix("../../images/main.png");
    ui->label->setPixmap(pix.scaled(window_width, window_height));

    QString style = "QPushButton{border: 1px solid transparent;text-align: center;"
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
                    "200, 200));}";

    ui->start->setText("Новая игра");
    ui->start->setStyleSheet(style);
    ui->local_board->setText("Локальная таблица рекордов");
    ui->local_board->setStyleSheet(style);
    ui->server_board->setText("Глобальная таблица рекордов");
    ui->server_board->setStyleSheet(style);
    ui->history->setText("История");
    ui->history->setStyleSheet(style);
    ui->exit->setText("Выход");
    ui->exit->setStyleSheet(style);

    ui->Eclipse->setText("Eclipse");
    ui->Eclipse->setStyleSheet(
        "background-color: rgba(0,0,0,0%); color : white;");
    QFont font;
    font.setWeight(QFont::ExtraBold);
    font.setPixelSize(point_size);
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
    damn->start_game();
}

void game_window::on_exit_clicked() {
    damn->cancel_game();
}

void game_window::set_god(God* damn_) {
    damn = damn_;
}

void game_window::on_local_board_clicked() {
    damn->show_leaderboard(local_leaderboard);
}

void game_window::on_history_clicked() {
    damn->show_legend_window();
}

void game_window::on_server_board_clicked() {
    damn->show_leaderboard(server_leaderboard);
}

