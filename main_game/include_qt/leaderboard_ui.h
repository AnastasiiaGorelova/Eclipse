

#ifndef MAIN_GAME_LEADERBOARD_UI_H
#define MAIN_GAME_LEADERBOARD_UI_H

#include <QTableWidget>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class local_leaderboard_ui;
}
QT_END_NAMESPACE

class local_leaderboard_ui : public QWidget {
  Q_OBJECT
public:
  explicit local_leaderboard_ui(QWidget *parent = nullptr);
  ~local_leaderboard_ui() override;

  void download_server_leaderboard();
  void download_local_leaderboard();

private:
  Ui::local_leaderboard_ui *ui;
  QTableWidget *table;
};

#endif // MAIN_GAME_LEADERBOARD_UI_H
