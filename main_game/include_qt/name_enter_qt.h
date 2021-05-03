//
// Created by alena on 03.05.2021.
//

#ifndef MAIN_GAME_NAME_ENTER_QT_H
#define MAIN_GAME_NAME_ENTER_QT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class name_enter_qt; }
QT_END_NAMESPACE

class name_enter_qt : public QWidget {
Q_OBJECT

public:
    explicit name_enter_qt(QWidget *parent = nullptr);

    ~name_enter_qt() override;

private:
    Ui::name_enter_qt *ui;
};

#endif //MAIN_GAME_NAME_ENTER_QT_H
