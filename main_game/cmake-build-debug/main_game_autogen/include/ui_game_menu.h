/********************************************************************************
** Form generated from reading UI file 'game_menu.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_MENU_H
#define UI_GAME_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_game_menu
{
public:

    void setupUi(QWidget *game_menu)
    {
        if (game_menu->objectName().isEmpty())
            game_menu->setObjectName(QString::fromUtf8("game_menu"));
        game_menu->resize(400, 300);

        retranslateUi(game_menu);

        QMetaObject::connectSlotsByName(game_menu);
    } // setupUi

    void retranslateUi(QWidget *game_menu)
    {
        game_menu->setWindowTitle(QApplication::translate("game_menu", "game_menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class game_menu: public Ui_game_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_MENU_H
