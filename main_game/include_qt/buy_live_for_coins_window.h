#ifndef MAIN_GAME_BUY_LIVE_FOR_COINS_WINDOW_H
#define MAIN_GAME_BUY_LIVE_FOR_COINS_WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <memory>
#include <QTimer>

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
    void buy_for_n_coins(int n, int k);
    void set_window_options();

private:
    int coins{};
    God* damn = nullptr;
    QTimer* timer = nullptr;

    QPushButton* yes_button = nullptr;
    QPushButton* no_button = nullptr;

    Ui::buy_live_for_coins_window *ui;
private slots:
    void _on_yes_button_clicked();
    void _on_no_button_clicked();
    void check_status();
};

#endif //MAIN_GAME_BUY_LIVE_FOR_COINS_WINDOW_H
