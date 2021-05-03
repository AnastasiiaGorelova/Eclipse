
#include <Key_Controller_.h>
#include <QApplication>
#include <iostream>

extern Modification_store train;

bool Key_Controller::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        auto *keyEvent = dynamic_cast<QKeyEvent *>(event);
        switch (keyEvent->key()) {
            case Qt::Key_Left:
                train.pushed_button_left();
                break;
            case Qt::Key_Right:
                train.pushed_button_right();
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
