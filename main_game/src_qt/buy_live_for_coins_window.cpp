
#include "buy_live_for_coins_window.h"
#include "ui_buy_live_for_coins_window.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "god.h"

#define window_width 400
#define window_height 300
#define point_size 30
#define timeout 1000 / 60

buy_live_for_coins_window::buy_live_for_coins_window(QWidget *parent)
    : QWidget(parent), ui(new Ui::buy_live_for_coins_window) {
  ui->setupUi(this);

  setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                  (*this).size(),
                                  qApp->desktop()->availableGeometry()));

  setFixedSize(window_width, window_height);
  setWindowTitle("Additional life");
}

buy_live_for_coins_window::~buy_live_for_coins_window() { delete ui; }

void buy_live_for_coins_window::_on_yes_button_clicked() {
  damn->gamer_choice = God::continue_game;
}

void buy_live_for_coins_window::_on_no_button_clicked() {
  damn->gamer_choice = God::stop_game;
}

void buy_live_for_coins_window::buy_for_n_coins(int n, int k) {
  coins = k;

  auto *vlay = new QVBoxLayout(this);
  vlay->setAlignment(Qt::AlignCenter);

  QFont font;
  font.setWeight(QFont::ExtraBold);
  font.setPixelSize(point_size);

  QString line = QString::fromStdString("Купить\n дополнительную жизнь\n за " +
                                        std::to_string(n) + " монет?\n");
  auto text = new QLabel(line);
  text->setParent(this);
  text->setStyleSheet("background-color: rgba(0,0,0,0%); color : white;");
  text->setFont(font);
  text->setAlignment(Qt::AlignCenter);
  vlay->addWidget(text);
  vlay->addWidget(yes_button);
  vlay->addWidget(no_button);

  this->setLayout(vlay);
}

void buy_live_for_coins_window::set_god(God *damn_) { damn = damn_; }

void buy_live_for_coins_window::check_status() {
  if (damn->gamer_choice == God::continue_game) {
    timer->stop();
    damn->add_life_and_restart_game(coins);
    damn->gamer_choice = God::wait;
  } else if (damn->gamer_choice == God::stop_game) {
    damn->controller_out.close_live_for_coins_window();
    damn->show_game_finish_window();
    damn->gamer_choice = God::wait;
  }
}

void buy_live_for_coins_window::set_window_options() {
  setWindowFlags(Qt::WindowMinimizeButtonHint);

  timer = new QTimer();
  timer->setParent(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(check_status()));
  timer->start(timeout);

  QPixmap backgroung("../../images/menu_background.png");
  backgroung = backgroung.scaled(this->size(), Qt::IgnoreAspectRatio);
  QPalette palette;
  palette.setBrush(QPalette::Background, backgroung);
  this->setPalette(palette);

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

  yes_button = new QPushButton("Да");
  yes_button->setParent(this);
  yes_button->setStyleSheet(style);

  no_button = new QPushButton("Нет");
  no_button->setParent(this);
  no_button->setStyleSheet(style);

  connect(no_button, &QPushButton::released, this,
          &buy_live_for_coins_window::_on_no_button_clicked);
  connect(yes_button, &QPushButton::released, this,
          &buy_live_for_coins_window::_on_yes_button_clicked);
}
