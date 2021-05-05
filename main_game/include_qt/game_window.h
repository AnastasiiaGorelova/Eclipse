#ifndef MAIN_GAME_GAME_WINDOW_H
#define MAIN_GAME_GAME_WINDOW_H
#include <QWidget>
#include <QVBoxLayout>
#include "main_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class game_window;
}
QT_END_NAMESPACE

class game_window : public QWidget {
    Q_OBJECT

public:
    explicit game_window(QWidget *parent = nullptr);
    ~game_window() override;

    void show_menu_first();

private:
    size_t width = 800;
    size_t height = 600;
    Ui::game_window *ui;

private slots:
    static void on_start_clicked();
    static void on_exit_clicked();
};

#endif  // MAIN_GAME_GAME_WINDOW_H
