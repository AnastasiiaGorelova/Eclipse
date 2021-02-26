

#ifndef MAIN_GAME_MAIN_WINDOW_H
#define MAIN_GAME_MAIN_WINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <unordered_map>
#include <include/asteroids_qt.h>


QT_BEGIN_NAMESPACE
namespace Ui { class main_window; }
QT_END_NAMESPACE

class main_window : public QWidget {
Q_OBJECT

public:
    explicit main_window(QWidget *parent = nullptr);
    ~main_window() override;

    QGraphicsScene* scene{};

    void make_field(int width, int height);
    void set(int x, int y, int size, const std::string& hash);
    void move(int x, int y, const std::string& hash);
    void end_game();


private:
    std::unordered_map<std::string, Asteroids_qt*> hash_table;
    Ui::main_window *ui;
};

#endif //MAIN_GAME_MAIN_WINDOW_H
