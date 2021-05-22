
#include "legend_window.h"
#include "ui_legend_window.h"
#include <QLabel>
#include <QStyle>
#include <QVBoxLayout>
#include <QDesktopWidget>

legend_window::legend_window(QWidget *parent)
    : QWidget(parent), ui(new Ui::legend_window) {
  ui->setupUi(this);

  QPixmap backgroung("../../images/menu_background.png"); //поменять картинку
  backgroung = backgroung.scaled(470, 500, Qt::IgnoreAspectRatio);
  QPalette palette;
  palette.setBrush(QPalette::Background, backgroung);
  this->setPalette(palette);

  auto *vlay = new QVBoxLayout(this);

  QFont font;
  font.setWeight(QFont::ExtraBold); // set font weight with enum QFont::Weight
  font.setPixelSize(20);            // this for setting font size

  auto text = new QLabel(
      "Землю атакуют астероиды и требуется\n самый отважный житель планеты для\n "
      "того, чтобы сдерживать атаку, пока\n земляне "
      "запрыгивают\n на спасательный шаттл.\n Вам предоставляется возможность\n "
      "сесть за штурвал космического корабля\n и задержать астероиды при помощи\n "
      "лазера. Требуется аккуратно и\n ответственно управлять пушкой, так как\n "
      "если астероид упадет на землю или\n на корабль, теряется одна из трех\n "
      "жизней. Как только жизни кончаются,\n планета захвачена, а значит люди не\n "
      "успели покинуть родную планету.\n Так как мы защищаем землю в одиночку,\n "
      "нам нужна помощь: во время сражения\n будут появляться дополнительные\n "
      "жизни, которые помогут\n выстоять долгую битву.\n");
  text->setParent(this);
  text->setStyleSheet("background-color: rgba(0,0,0,0%); color : white;");
  text->setFont(font);
  text->setAlignment(Qt::AlignCenter);
  vlay->addWidget(text);

  vlay->setAlignment(Qt::AlignCenter);
  this->setLayout(vlay);

  setWindowTitle("Legend");
  setFixedSize(470, 500);

  setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                  (*this).size(),
                                  qApp->desktop()->availableGeometry()));
}

legend_window::~legend_window() { delete ui; }
