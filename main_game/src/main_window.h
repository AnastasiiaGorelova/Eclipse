

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
    void set(int x, int y, int size, int hash, std::string name);
    void move(int x, int y, int hash);
    void end_game();


private:
    enum Img {
        ASTEROID,
        LIFE,
        SPACE_SHIP,
        SHOT
    };

    std::unordered_map<int, eclipse::Asteroids_qt*> hash_table;
    Ui::main_window *ui;
};

#endif //MAIN_GAME_MAIN_WINDOW_H
