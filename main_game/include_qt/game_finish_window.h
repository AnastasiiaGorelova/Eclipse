

#ifndef MAIN_GAME_GAME_FINISH_WINDOW_H
#define MAIN_GAME_GAME_FINISH_WINDOW_H

#include <QWidget>

class God;

QT_BEGIN_NAMESPACE
namespace Ui { class game_finish_window; }
QT_END_NAMESPACE

class game_finish_window : public QWidget {
Q_OBJECT

public:
    God* damn;

    explicit game_finish_window(QWidget *parent = nullptr);
    ~game_finish_window() override;

    void set_god(God* damn_);
private:
    Ui::game_finish_window *ui;
};

#endif //MAIN_GAME_GAME_FINISH_WINDOW_H
