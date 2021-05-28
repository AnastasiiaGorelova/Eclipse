
#include "selection.h"
#include "ui_Selection.h"
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <god.h>

#define window_width 400
#define window_height 300
#define point_size 35

Selection::Selection(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Selection) {
  ui->setupUi(this);

  setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                  (*this).size(),
                                  qApp->desktop()->availableGeometry()));

  setWindowTitle("Set Controller");
  setFixedSize(window_width, window_height);

  setWindowFlags(Qt::WindowMinimizeButtonHint);

  QPixmap backgroung("../../images/menu_background.png");
  backgroung = backgroung.scaled(this->size(), Qt::IgnoreAspectRatio);
  QPalette palette;
  palette.setBrush(QPalette::Background, backgroung);
  this->setPalette(palette);

  auto *wdg = new QWidget(this);
  auto *vlay = new QVBoxLayout(wdg);

  QFont font;
  font.setWeight(QFont::ExtraBold);
  font.setPixelSize(point_size);

  auto text = new QLabel("Выберите\n тип управления\n");
  text->setParent(this);
  text->setStyleSheet("background-color: rgba(0,0,0,0%); color : white;");
  text->setFont(font);
  text->setAlignment(Qt::AlignCenter);
  vlay->addWidget(text);

  QString style =
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
      "200, 200));}";

  key = new QPushButton("Клавиатура");
  key->setParent(this);
  key->setStyleSheet(style);
  vlay->addWidget(key);
  ard = new QPushButton("Arduino");
  ard->setParent(this);
  ard->setStyleSheet(style);
  vlay->addWidget(ard);

  vlay->setAlignment(Qt::AlignCenter);
  wdg->setLayout(vlay);
  setCentralWidget(wdg);

  connect(key, &QPushButton::released, this, &Selection::_on_key_clicked);
  connect(ard, &QPushButton::released, this, &Selection::_on_ard_clicked);
}

Selection::~Selection() { delete ui; }

void Selection::_on_key_clicked() const {
  damn->select_game_controller(eclipse::Key);
}

void Selection::_on_ard_clicked() const {
  damn->select_game_controller(eclipse::Arduino);
}

void Selection::set_god(God *damn_) { damn = damn_; }
