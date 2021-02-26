/********************************************************************************
** Form generated from reading UI file 'game_window.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_WINDOW_H
#define UI_GAME_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_game_window
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *start;
    QPushButton *exit;
    QLabel *label;

    void setupUi(QWidget *game_window)
    {
        if (game_window->objectName().isEmpty())
            game_window->setObjectName(QString::fromUtf8("game_window"));
        game_window->resize(800, 600);
        verticalLayoutWidget = new QWidget(game_window);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(240, 290, 321, 221));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        start = new QPushButton(verticalLayoutWidget);
        start->setObjectName(QString::fromUtf8("start"));

        verticalLayout->addWidget(start);

        exit = new QPushButton(verticalLayoutWidget);
        exit->setObjectName(QString::fromUtf8("exit"));

        verticalLayout->addWidget(exit);

        label = new QLabel(game_window);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 801, 601));
        label->raise();
        verticalLayoutWidget->raise();

        retranslateUi(game_window);

        QMetaObject::connectSlotsByName(game_window);
    } // setupUi

    void retranslateUi(QWidget *game_window)
    {
        game_window->setWindowTitle(QApplication::translate("game_window", "game_window", nullptr));
        start->setText(QApplication::translate("game_window", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\270\320\263\321\200\321\203", nullptr));
        exit->setText(QApplication::translate("game_window", "\320\222\321\213\320\271\321\202\320\270", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class game_window: public Ui_game_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_WINDOW_H
