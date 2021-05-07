#ifndef MAIN_GAME_BUY_LIVE_FOR_COINS_WINDOW_H
#define MAIN_GAME_BUY_LIVE_FOR_COINS_WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <memory>

class God;

QT_BEGIN_NAMESPACE
namespace Ui { class buy_live_for_coins_window; }
QT_END_NAMESPACE

class buy_live_for_coins_window : public QWidget {
Q_OBJECT

public:

    explicit buy_live_for_coins_window(QWidget *parent = nullptr);
    ~buy_live_for_coins_window() override;

    void set_god(God* damn_);
    void buy_for_n_coins(int n);

private:
    Ui::buy_live_for_coins_window *ui;

    God* damn;

    QPushButton* yes_button;
    QPushButton* no_button;

private slots:
    void _on_yes_button_clicked();
    void _on_no_button_clicked();
};

#endif //MAIN_GAME_BUY_LIVE_FOR_COINS_WINDOW_H
