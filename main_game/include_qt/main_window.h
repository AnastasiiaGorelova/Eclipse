#ifndef MAIN_GAME_MAIN_WINDOW_H
#define MAIN_GAME_MAIN_WINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <unordered_map>
#include <include_qt/GameObject.h>

QT_BEGIN_NAMESPACE
namespace Ui { class main_window; }
QT_END_NAMESPACE

class main_window : public QWidget {
Q_OBJECT

public:
    explicit main_window(QWidget *parent = nullptr);
    ~main_window() override;

    QGraphicsScene* scene{};

    void make_field();
    void set(int x, int y, int size, const std::string& hash, const std::string& object_name);
    void delete_obj (const std::string& hash);
    void move(int x, int y, const std::string& hash);

private:
    size_t width = 800;
    size_t height = 600;
    std::unordered_map<std::string, GameObject*> hash_table;
    Ui::main_window *ui;

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif //MAIN_GAME_MAIN_WINDOW_H
