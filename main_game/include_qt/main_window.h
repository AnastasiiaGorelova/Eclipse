#ifndef MAIN_GAME_MAIN_WINDOW_H
#define MAIN_GAME_MAIN_WINDOW_H

#include <GameObject.h>
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

    std::unordered_map<std::string, GameObject *> hash_table;
    God* damn;
public:
    std::pair<std::string, std::string> get_cur_time();

    void start_timer_for_beginning();
    void add_life();

    explicit main_window(QWidget *parent = nullptr);
    ~main_window() override;

    QGraphicsScene *scene{};
    QGraphicsScene *scene_info{};

    QLabel *time;
    QLabel *number_for_time;
    QLabel *coins_counter;

    QTimer *timer_for_start;
    QTimer *timer;
    QTimer *timer_for_ticks;
    QTimer *timer_for_shots;
    QTimer *timer_for_monster;

    void make_field();
    void set(int x,
             int y,
             int size,
             const std::string &hash,
             const std::string &object_name);
    void delete_obj(const std::string &hash);
    void move(int x, int y, const std::string &hash);

    void start_timer();

    void set_timer();
    void set_lives();
    void set_coins_counter();

    void change_coins_counter(int count) const;
    void decrease_lives();
    void change_asteroid_crack(const std::string &hash, int size);
    void set_God(God* damn_);

private slots:
    void change_timer();
    void tick_god();
    void make_shot();
    void change_label();
    void tick_god_with_monster();

private:

    int time_for_start = 0;
    QLabel *text;
    QVBoxLayout *vlay;
    size_t width = 800;
    size_t height = 600;
    Ui::main_window *ui;

    int cur_time = 0;
    static std::pair<std::string, std::string> find_time_string(int x);
};

#endif// MAIN_GAME_MAIN_WINDOW_H
