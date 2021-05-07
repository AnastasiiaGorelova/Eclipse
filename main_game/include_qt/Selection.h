
#ifndef MAIN_GAME_SELECTION_H
#define MAIN_GAME_SELECTION_H

#include <QMainWindow>
#include <QPushButton>
#include <QStyle>
#include <QDesktopWidget>

class God;

QT_BEGIN_NAMESPACE
namespace Ui { class Selection; }
QT_END_NAMESPACE

class Selection : public QMainWindow {
Q_OBJECT

public:
    God* damn;

    explicit Selection(QWidget *parent = nullptr);
    ~Selection() override;

    void set_god(God* damn_);

private:
    Ui::Selection *ui;

    QPushButton *key;
    QPushButton *ard;

private slots:
    void _on_key_clicked();
    void _on_ard_clicked();

};

#endif //MAIN_GAME_SELECTION_H
