#ifndef MAIN_GAME_MAIN_WINDOW_H
#define MAIN_GAME_MAIN_WINDOW_H

#include <game_object.h>
#include <QGraphicsScene>
#include <QLabel>
#include <QTimer>
#include <QWidget>
#include <unordered_map>
#include <QVBoxLayout>

class God;

QT_BEGIN_NAMESPACE
namespace Ui {
    class main_window;
}
QT_END_NAMESPACE

class main_window : public QWidget {
    Q_OBJECT
public:
    explicit main_window(QWidget *parent = nullptr);
    ~main_window() override;

    void make_field();
    void set(int x,
             int y,
             int size,
             const std::string &hash,
             const std::string &object_name);
    void delete_obj(const std::string &hash);
    void move(int x, int y, const std::string &hash);

    void set_timer();
    void set_lives();
    void set_coins_counter();
    void set_God(God* damn_);

    std::pair<std::string, std::string> get_cur_time();

    void add_life();
    void decrease_lives();
    void change_coins_counter(int count) const;
    void change_asteroid_crack(const std::string &hash, int size);
    void set_game_on_pause();

    void start_timer();
    void start_timer_for_beginning();

    QTimer *timer_for_start = nullptr;
    QTimer *timer = nullptr;
    QTimer *timer_for_ticks = nullptr;
    QTimer *timer_for_shots = nullptr;
    QTimer *timer_for_monster = nullptr;
    QTimer *timer_for_pause = nullptr;

    QLabel *text = nullptr;

private slots:
    void change_timer();
    void tick_god();
    void make_shot();
    void change_label();
    void tick_god_with_monster();
    void check_keys();

private:
    enum enemy {
        asteroids,
        alien
    };

    enemy cur_enemy = asteroids;

    Ui::main_window *ui;

    God* damn;

    QGraphicsScene *scene = nullptr;
    QGraphicsScene *scene_info = nullptr;

    QLabel *time = nullptr;
    QLabel *number_for_time = nullptr;
    QLabel *coins_counter = nullptr;

    QVBoxLayout *vlay = nullptr;

    int cur_time = 0;

    std::unordered_map<std::string, GameObject *> hash_table;
    static std::pair<std::string, std::string> find_time_string(int x);
};

#endif// MAIN_GAME_MAIN_WINDOW_H
