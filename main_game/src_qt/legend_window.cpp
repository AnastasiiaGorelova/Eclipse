
#include "legend_window.h"
#include "ui_legend_window.h"
#include <QLabel>
#include <QStyle>
#include <QVBoxLayout>
#include <QDesktopWidget>

#define window_width 470
#define window_height 500
#define point_size 18

legend_window::legend_window(QWidget *parent)
    : QWidget(parent), ui(new Ui::legend_window) {
  ui->setupUi(this);

  setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                    (*this).size(),
                                    qApp->desktop()->availableGeometry()));

  setWindowTitle("Legend");
  setFixedSize(window_width, window_height);

  setGeometry(
            QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    this->size(),
                    qApp->desktop()->availableGeometry()
            )
    );


  QPixmap backgroung("../../images/background_manual.png"); //поменять картинку
  backgroung = backgroung.scaled(window_width, window_height, Qt::IgnoreAspectRatio);
  QPalette palette;
  palette.setBrush(QPalette::Background, backgroung);
  this->setPalette(palette);

  auto *vlay = new QVBoxLayout(this);

  QFont font;
  font.setWeight(QFont::ExtraBold);
  font.setPixelSize(point_size);

  auto text = new QLabel(
      "Землю атакуют астероиды и требуется\n самый отважный житель планеты.\n "
      "Главному герою необходимо сдерживать\n атаку, пока земляне запрыгивают\n на спасательный шаттл.\n "
      "Игроку предоставляется возможность\n сесть за штурвал космического корабля\n "
      "и задержать астероиды\n при помощи лазеров.\n Требуется аккуратно управлять пушкой,\n"
      " ведь если астероид врежется\n в Землю или в корпус корабля,\n теряется одна из трех жизней.\n"
      " Как только жизни кончаются,\n планета разрушена\n и люди не успели спастись.\n "
      "Так как мы защищаем землю в одиночку,\n нам нужна помощь: во время сражения\n "
      "будут появляться дополнительные жизни,\n которые помогут выстоять долгое сражение.\n");
  text->setParent(this);
  text->setStyleSheet("background-color: rgba(0,0,0,0%); color : white;");
  text->setFont(font);
  text->setAlignment(Qt::AlignCenter);
  vlay->addWidget(text);
  this->setLayout(vlay);

}

legend_window::~legend_window() { delete ui; }
