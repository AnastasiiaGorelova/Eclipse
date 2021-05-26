
#include "game_finish_window.h"
#include <QLabel>
#include <QVBoxLayout>
#include "god.h"
#include "ui_game_finish_window.h"

#define window_width 400
#define window_height 300
#define point_size 35

game_finish_window::game_finish_window(QWidget *parent)
    : QWidget(parent), ui(new Ui::game_finish_window) {
    ui->setupUi(this);

    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                    (*this).size(),
                                    qApp->desktop()->availableGeometry()));

    setWindowTitle("Game over");
    setFixedSize(window_width, window_height);

    setWindowFlags(Qt::WindowMinimizeButtonHint);

    QPixmap backgroung("../../images/menu_background.png");  //поменять картинку
    backgroung = backgroung.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, backgroung);
    this->setPalette(palette);
}

game_finish_window::~game_finish_window() {
    delete ui;
}

void game_finish_window::set_god(God *damn_) {
    damn = damn_;

    auto *vlay = new QVBoxLayout(this);
    vlay->setAlignment(Qt::AlignCenter);

    QFont font;
    font.setWeight(
            QFont::ExtraBold);
    font.setPixelSize(point_size);

    auto text = new QLabel("Конец игры!");
    text->setParent(this);
    text->setStyleSheet("background-color: rgba(0,0,0,0%); color : white;");
    text->setFont(font);
    text->setAlignment(Qt::AlignCenter);
    vlay->addWidget(text);

    QString score_text =
            "Имя: " + QString::fromStdString(damn->cur_player.name) + "\n" +
            "Время: " + QString::fromStdString(damn->get_time()) + "\n";
    auto score = new QLabel(score_text);
    score->setParent(this);
    score->setStyleSheet("background-color: rgba(0,0,0,0%); color : white;");
    score->setFont(font);
    score->setAlignment(Qt::AlignCenter);
    vlay->addWidget(score);

    back_to_menu = new QPushButton("Вернуться в меню");
    back_to_menu->setParent(this);
    back_to_menu->setStyleSheet(
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
    vlay->addWidget(back_to_menu);

    connect(back_to_menu, &QPushButton::released, this, &game_finish_window::_on_continue_game_clicked);

    this->setLayout(vlay);
}

void game_finish_window::_on_continue_game_clicked() const {
    damn->close_game_finish_window();
    damn->show_menu();
}
