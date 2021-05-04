
#ifndef MAIN_GAME_ERROR_MASSAGE_WINDOW_H
#define MAIN_GAME_ERROR_MASSAGE_WINDOW_H

#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class error_massage_window; }
QT_END_NAMESPACE

class error_massage_window : public QWidget {
Q_OBJECT

public:
    explicit error_massage_window(QWidget *parent = nullptr);

    ~error_massage_window() override;

    void arduino_setting_error();

private:
    Ui::error_massage_window *ui;
    QPushButton *back_to_selection_window;

    void _on_back_to_menu_clicked();
};

#endif //MAIN_GAME_ERROR_MASSAGE_WINDOW_H
