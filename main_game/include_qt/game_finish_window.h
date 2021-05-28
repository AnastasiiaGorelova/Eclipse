

#ifndef MAIN_GAME_GAME_FINISH_WINDOW_H
#define MAIN_GAME_GAME_FINISH_WINDOW_H

#include <QPushButton>
#include <QWidget>

class God;

QT_BEGIN_NAMESPACE
namespace Ui {
class game_finish_window;
}
QT_END_NAMESPACE

class game_finish_window : public QWidget {
  Q_OBJECT

public:
  explicit game_finish_window(QWidget *parent = nullptr);
  ~game_finish_window() override;

  void set_god(God *damn_);

private:
  Ui::game_finish_window *ui;

  God *damn;
  QPushButton *back_to_menu;

private slots:
  void _on_continue_game_clicked() const;
};

#endif // MAIN_GAME_GAME_FINISH_WINDOW_H
