
#ifndef MAIN_GAME_GAME_WINDOW_H
#define MAIN_GAME_GAME_WINDOW_H

#include <QWidget>
#include "../include/main_window.h"
#include "../include/God.h"

extern God damn;

QT_BEGIN_NAMESPACE
namespace Ui { class game_window; }
QT_END_NAMESPACE

class game_window : public QWidget {
Q_OBJECT

public:
    explicit game_window(QWidget *parent = nullptr);
    ~game_window() override;

    void show_menu_first(size_t width_, size_t height_);
    void start();
    void stop_game();

private slots:
    static void on_start_clicked();
    static void on_exit_clicked();

private:
    main_window main_view;
    size_t width{};
    size_t height{};
    Ui::game_window *ui;
};

#endif //MAIN_GAME_GAME_WINDOW_H
