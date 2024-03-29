
#ifndef MAIN_GAME_KEY_CONTROLLER_H
#define MAIN_GAME_KEY_CONTROLLER_H

#include "controllers_in.h"
#include <QEvent>
#include <QKeyEvent>
#include <QObject>

class God;

struct Key_Controller : QObject, virtual Controller_in {
  void set_God(God *damn_) override;

  explicit Key_Controller(QObject *parent = nullptr);
  bool eventFilter(QObject *obj, QEvent *event) override;
  void write_to_port_for_coins() override;
};

#endif // MAIN_GAME_KEY_CONTROLLER_H
