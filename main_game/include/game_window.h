//
// Created by alena on 18.02.2021.
//

#ifndef MAIN_GAME_GAME_WINDOW_H
#define MAIN_GAME_GAME_WINDOW_H

#include <QWidget>
#include "../include/game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class game_window; }
QT_END_NAMESPACE

class game_window : public QWidget {
Q_OBJECT

public:
    explicit game_window(QWidget *parent = nullptr);
    ~game_window() override;


private slots:
    void on_start_clicked();
    static void on_exit_clicked();

private:
    Ui::game_window *ui;
};

#endif //MAIN_GAME_GAME_WINDOW_H
