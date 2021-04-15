
#ifndef MAIN_GAME_SELECTION_H
#define MAIN_GAME_SELECTION_H

#include <QMainWindow>
#include <QPushButton>
#include <QStyle>
#include <QDesktopWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Selection; }
QT_END_NAMESPACE

class Selection : public QMainWindow {
Q_OBJECT

public:
    explicit Selection(QWidget *parent = nullptr);

    ~Selection() override;

private:
    Ui::Selection *ui;

    QPushButton *key;
    QPushButton *ard;

private slots:
    void on_key_clicked();
    void on_ard_clicked();

};

#endif //MAIN_GAME_SELECTION_H
