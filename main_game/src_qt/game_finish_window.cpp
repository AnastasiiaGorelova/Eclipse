
#include <QVBoxLayout>
#include <QLabel>
#include "God.h"
#include "game_finish_window.h"
#include "ui_game_finish_window.h"

extern God damn;

game_finish_window::game_finish_window(QWidget *parent) :
        QWidget(parent), ui(new Ui::game_finish_window) {

    ui->setupUi(this);

    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                    (*this).size(),
                                    qApp->desktop()->availableGeometry()));


    QPixmap backgroung("../../images/menu_background.png"); //поменять картинку
    backgroung = backgroung.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, backgroung);
    this->setPalette(palette);

    auto *vlay = new QVBoxLayout(this);
    vlay->setAlignment(Qt::AlignCenter);

    QFont font;
    font.setWeight(QFont::ExtraBold); // set font weight with enum QFont::Weight
    font.setPixelSize(35); // this for setting font size

    auto text = new QLabel("Конец игры!");
    text->setStyleSheet("background-color: rgba(0,0,0,0%); color : white;");
    text->setFont(font);
    text->setAlignment(Qt::AlignCenter);
    vlay -> addWidget(text);

    QString score_text = "Имя: " + QString::fromStdString(damn.player_name) + "\n" + "Время: " + QString::fromStdString(damn.get_time()) + "\n";
    auto score = new QLabel(score_text);
    score->setStyleSheet("background-color: rgba(0,0,0,0%); color : white;");
    score->setFont(font);
    score->setAlignment(Qt::AlignCenter);
    vlay -> addWidget(score);

    vlay->setAlignment(Qt::AlignCenter);
    this->setLayout(vlay);

    setWindowTitle("Game over!");
    setFixedSize(400, 300);
}

game_finish_window::~game_finish_window() {
    delete ui;
}
