#ifndef MAIN_GAME_NAME_ENTER_QT_H
#define MAIN_GAME_NAME_ENTER_QT_H

#include <QWidget>
#include <QLineEdit>
#include <QDialogButtonBox>

class God;

QT_BEGIN_NAMESPACE
namespace Ui { class name_enter_qt; }
QT_END_NAMESPACE

class name_enter_qt : public QWidget {
Q_OBJECT

public:
    explicit name_enter_qt(QWidget *parent = nullptr);
    ~name_enter_qt() override;

    void set_god(God* damn_);

private:
    Ui::name_enter_qt *ui;
    QLineEdit *echoLineEdit;
    God* damn;
    void _line_edit();
};

#endif //MAIN_GAME_NAME_ENTER_QT_H
