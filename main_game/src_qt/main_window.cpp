#include "main_window.h"
#include "god.h"
#include "ui_main_window.h"
#include <QDesktopWidget>
#include <QGraphicsProxyWidget>
#include <QKeyEvent>
#include <QStyle>

#define window_width 800
#define window_height 630
#define play_field_height 600
#define point_size 200
#define scene_info_height 30
#define lives_and_coins_size 25
#define timer_for_shots_timeout 1000 / 1.6
#define timer_for_start_timeout 1200
#define timer_timeout 1000
#define text_timer_width 100
#define text_timer_height 30
#define text_timer_pos_width 10
#define text_timer_pos_height 7
#define text_timer_counters_pos_width 60
#define text_timer_counters_pos_height 7
#define lives1_pos_width 700
#define lives2_pos_width 730
#define lives3_pos_width 760
#define lives_and_coins_pos_height 3.5
#define text_coins_pos_width 620
#define text_coins_pos_height 7
#define coins_pos_width 640
#define alien_timeout_come_in_sec 15

main_window::main_window(QWidget *parent)
    : QWidget(parent), ui(new Ui::main_window) {
  ui->setupUi(this);

  setFixedSize(window_width, window_height);
  setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                  (*this).size(),
                                  qApp->desktop()->availableGeometry()));
}

main_window::~main_window() { delete ui; }

void main_window::make_field() {
  scene = new QGraphicsScene();
  scene->setParent(this);
  scene->setSceneRect(0, 0, window_width, play_field_height);
  ui->graphicsView->setScene(scene);
  scene->setBackgroundBrush(QBrush(QImage("../../images/background.png")
                                       .scaled(window_width, window_height)));
  ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView->setFrameShape(QFrame::NoFrame);

  scene_info = new QGraphicsScene();
  scene_info->setSceneRect(0, 0, window_width, scene_info_height);
  ui->graphicsView_2->setScene(scene_info);
  scene_info->setBackgroundBrush(Qt::black);
  ui->graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->graphicsView_2->setFrameShape(QFrame::NoFrame);

  setWindowTitle("Eclipse");

  vlay = new QVBoxLayout(this);
  vlay->setAlignment(Qt::AlignCenter);

  QFont font;
  font.setWeight(QFont::ExtraBold);
  font.setPixelSize(point_size);

  text = new QLabel("");
  text->setParent(this);
  text->setStyleSheet("background-color: rgba(0,0,0,0%); color : white;");
  text->setFont(font);
  text->setAlignment(Qt::AlignCenter);
  vlay->addWidget(text);
}

void main_window::set(int x, int y, int size, const std::string &hash,
                      const std::string &object_name) {
  auto *object = new GameObject();
  object->setParent(this);
  QString filename =
      "../../images/" + QString::fromStdString(object_name) + ".png";
  object->setPixmap(QPixmap(filename).scaled(size, size));
  object->setPos(x, y);
  scene->addItem(object);
  hash_table[hash] = object;
}

void main_window::move(int x, int y, const std::string &hash) {
  if (hash_table[hash] != nullptr) {
    hash_table[hash]->setPos(x, y);
  }
}

void main_window::delete_obj(const std::string &hash) {
  if (hash_table[hash] != nullptr) {
    hash_table[hash]->del();
    hash_table[hash] = nullptr;
  }
}

void main_window::set_timer() {
  time = new QLabel("Time:");
  time->setStyleSheet("background-color: black; color : white;");
  number_for_time = new QLabel("00:00");
  number_for_time->setStyleSheet("background-color: black; color : white;");

  auto *item_1 = new QGraphicsRectItem;
  item_1->setRect(QRect(0, 0, text_timer_width, text_timer_height));
  scene_info->addItem(item_1);
  auto *pMyProxy_1 = new QGraphicsProxyWidget(item_1);
  pMyProxy_1->setWidget(time);
  pMyProxy_1->setPos(text_timer_pos_width, text_timer_pos_height);

  auto *item_2 = new QGraphicsRectItem;
  item_2->setRect(QRect(0, 0, text_timer_width, text_timer_height));
  scene_info->addItem(item_2);
  auto *pMyProxy_2 = new QGraphicsProxyWidget(item_2);
  pMyProxy_2->setWidget(number_for_time);
  pMyProxy_2->setPos(text_timer_counters_pos_width,
                     text_timer_counters_pos_height);
}

void main_window::set_lives() {
  auto img_heart = QPixmap("../../images/heart.png")
                       .scaled(lives_and_coins_size, lives_and_coins_size);
  auto *object_1 = new GameObject();
  object_1->setParent(this);
  object_1->setPixmap(img_heart);
  scene_info->addItem(object_1);
  object_1->setPos(lives1_pos_width, lives_and_coins_pos_height);
  hash_table["heart_1"] = object_1;

  auto *object_2 = new GameObject();
  object_2->setParent(this);
  object_2->setPixmap(img_heart);
  object_2->setPos(lives2_pos_width, lives_and_coins_pos_height);
  scene_info->addItem(object_2);
  hash_table["heart_2"] = object_2;

  auto *object_3 = new GameObject();
  object_3->setParent(this);
  object_3->setPixmap(img_heart);
  object_3->setPos(lives3_pos_width, lives_and_coins_pos_height);
  scene_info->addItem(object_3);
  hash_table["heart_3"] = object_3;
}

void main_window::decrease_lives() {
  if (hash_table.find("heart_1") != hash_table.end()) {
    hash_table["heart_1"]->del();
    hash_table.erase("heart_1");
  } else if (hash_table.find("heart_2") != hash_table.end()) {
    hash_table["heart_2"]->del();
    hash_table.erase("heart_2");
  } else if (hash_table.find("heart_3") != hash_table.end()) {
    hash_table["heart_3"]->del();
    hash_table.erase("heart_3");
  }
}

void main_window::change_timer() {
  cur_time++;
  auto [min, sec] = find_time_string(cur_time);
  QString time_string =
      QString::fromStdString(min) + ":" + QString::fromStdString(sec);
  number_for_time->setText(time_string);
}

std::pair<std::string, std::string> main_window::find_time_string(int x) {
  std::string min = std::to_string(x / 60);
  if (min.size() == 0) {
    min = "00";
  }
  if (min.size() == 1) {
    min = "0" + min;
  }
  std::string sec = std::to_string(x % 60);
  if (sec.size() == 0) {
    min = "00";
  }
  if (sec.size() == 1) {
    sec = "0" + sec;
  }
  return std::pair<std::string, std::string>(min, sec);
}

void main_window::start_timer() {
  timer = new QTimer();
  timer->setParent(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(change_timer()));
  timer->start(timer_timeout);

  timer_for_ticks = new QTimer();
  timer_for_ticks->setParent(this);
  connect(timer_for_ticks, SIGNAL(timeout()), this, SLOT(tick_god()));
  timer_for_ticks->start(1000 / ticks_for_second);

  timer_for_shots = new QTimer();
  timer_for_shots->setParent(this);
  connect(timer_for_shots, SIGNAL(timeout()), this, SLOT(make_shot()));
  timer_for_shots->start(timer_for_shots_timeout);

  timer_for_monster = new QTimer();
  timer_for_monster->setParent(this);
  connect(timer_for_monster, SIGNAL(timeout()), this,
          SLOT(tick_god_with_monster()));
}

void main_window::tick_god() {
  static int time_lasts = 0;
  time_lasts++;
  if (time_lasts == alien_timeout_come_in_sec * ticks_for_second) {
    time_lasts = 0;
    timer_for_ticks->stop();
    cur_enemy = alien;
    damn->game->alien.change_state(eclipse::Going_out);
    timer_for_monster->start(1000 / ticks_for_second);
    return;
  }
  damn->make_move_in_logic_and_ui();
}

void main_window::make_shot() { damn->make_shoot(); }

std::pair<std::string, std::string> main_window::get_cur_time() {
  return find_time_string(cur_time);
}

void main_window::change_asteroid_crack(const std::string &hash, int size) {
  hash_table[hash]->setPixmap(
      QPixmap("../../images/broken_asteroid.png").scaled(size, size));
}

void main_window::change_label() {
  static int time_for_start = 0;
  time_for_start++;
  if (time_for_start < 4) {
    text->setText(QString::fromStdString(std::to_string(4 - time_for_start)));
  } else if (time_for_start == 4) {
    text->setText("GO!");
  } else {
    time_for_start = 0;
    timer_for_start->stop();
    text->setText("");
    damn->start_timers();
  }
}

void main_window::start_timer_for_beginning() {
  timer_for_start = new QTimer();
  timer_for_start->setParent(this);
  connect(timer_for_start, SIGNAL(timeout()), this, SLOT(change_label()));
  timer_for_start->start(timer_for_start_timeout);
}

void main_window::set_coins_counter() {
  auto img_coin = QPixmap("../../images/coin.png")
                      .scaled(lives_and_coins_size, lives_and_coins_size);
  auto *object_1 = new GameObject();
  object_1->setPixmap(img_coin);
  object_1->setParent(this);
  scene_info->addItem(object_1);
  object_1->setPos(coins_pos_width, lives_and_coins_pos_height);
  hash_table["coin_img"] = object_1;

  auto *item_1 = new QGraphicsRectItem;
  item_1->setRect(QRect(0, 0, text_timer_width, text_timer_height));
  scene_info->addItem(item_1);
  auto *pMyProxy_1 = new QGraphicsProxyWidget(item_1);
  coins_counter = new QLabel("  0  ");
  coins_counter->setStyleSheet("background-color: black; color : white;");
  pMyProxy_1->setWidget(coins_counter);
  pMyProxy_1->setPos(text_coins_pos_width, text_coins_pos_height);
}

void main_window::change_coins_counter(int count) const {
  coins_counter->setText(QString::fromStdString(std::to_string(count)));
}

void main_window::add_life() {
  auto img_heart = QPixmap("../../images/heart.png")
                       .scaled(lives_and_coins_size, lives_and_coins_size);
  if (hash_table.find("heart_3") == hash_table.end()) {
    auto *object_3 = new GameObject();
    object_3->setParent(this);
    object_3->setPixmap(img_heart);
    object_3->setPos(lives3_pos_width, lives_and_coins_pos_height);
    scene_info->addItem(object_3);
    hash_table["heart_3"] = object_3;
  } else if (hash_table.find("heart_2") == hash_table.end()) {
    auto *object_2 = new GameObject();
    object_2->setParent(this);
    object_2->setPixmap(img_heart);
    object_2->setPos(lives2_pos_width, lives_and_coins_pos_height);
    scene_info->addItem(object_2);
    hash_table["heart_2"] = object_2;
  } else if (hash_table.find("heart_1") == hash_table.end()) {
    auto *object_1 = new GameObject();
    object_1->setParent(this);
    object_1->setPixmap(img_heart);
    scene_info->addItem(object_1);
    object_1->setPos(lives1_pos_width, lives_and_coins_pos_height);
    hash_table["heart_1"] = object_1;
  }
}

void main_window::set_God(God *damn_) { damn = damn_; }

void main_window::tick_god_with_monster() {
  if (damn->game->alien.get_state() == eclipse::Not_on_the_field) {
    timer_for_monster->stop();
    ten_points_acceleration();
    cur_enemy = asteroids;
    timer_for_ticks->start(1000 / ticks_for_second);
    return;
  }
  damn->make_move_in_logic_and_ui_with_monster();
}

void main_window::set_game_on_pause() {
  text->setText("| |");

  timer_for_pause = new QTimer();
  timer_for_pause->setParent(this);
  connect(timer_for_pause, SIGNAL(timeout()), this, SLOT(check_keys()));
  timer_for_pause->start(timer_for_start_timeout);
}

void main_window::check_keys() {
  auto status = damn->train.get_aggregated_changes();
  if (status == eclipse::kChangeGameState) {
    text->setText("");
    timer_for_pause->stop();
    timer_for_shots->start();
    timer->start();
    if (cur_enemy == asteroids) {
      timer_for_ticks->start();
    } else {
      timer_for_monster->start();
    }
  }
}

void main_window::ten_points_acceleration() {
  if (ticks_for_second < 120) {
    ticks_for_second += 10;
    damn->change_game_speed(10);
  }
}
