#include "god.h"
#include <QApplication>
#include <key_controller.h>

bool Key_Controller::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() == QEvent::KeyPress) {
    auto *keyEvent = dynamic_cast<QKeyEvent *>(event);
    switch (keyEvent->key()) {
    case Qt::Key_Left:
      damn->modificationStore.pushed_button_left();
      break;
    case Qt::Key_Right:
      damn->modificationStore.pushed_button_right();
      break;
    case Qt::Key_Space:
      damn->modificationStore.pushed_pause_or_play();
      break;
    default:
      break;
    }
  }
  return QObject::eventFilter(obj, event);
}

Key_Controller::Key_Controller(QObject *parent) : QObject(parent) {
  qApp->installEventFilter(this);
}

void Key_Controller::set_God(God *damn_) { damn = damn_; }
void Key_Controller::write_to_port_for_coins() {}
