//
// Created by alena on 22.05.2021.
//

#ifndef MAIN_GAME_LEGEND_WINDOW_H
#define MAIN_GAME_LEGEND_WINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class legend_window; }
QT_END_NAMESPACE

class legend_window : public QWidget {
Q_OBJECT

public:
    explicit legend_window(QWidget *parent = nullptr);

    ~legend_window() override;

private:
    Ui::legend_window *ui;
};

#endif //MAIN_GAME_LEGEND_WINDOW_H
