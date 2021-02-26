/********************************************************************************
** Form generated from reading UI file 'game_field.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_FIELD_H
#define UI_GAME_FIELD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_game_field
{
public:
    QGraphicsView *graphicsView;

    void setupUi(QWidget *game_field)
    {
        if (game_field->objectName().isEmpty())
            game_field->setObjectName(QString::fromUtf8("game_field"));
        graphicsView = new QGraphicsView(game_field);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 811, 501));

        retranslateUi(game_field);

        QMetaObject::connectSlotsByName(game_field);
    } // setupUi

    void retranslateUi(QWidget *game_field)
    {
        game_field->setWindowTitle(QApplication::translate("game_field", "game_field", nullptr));
    } // retranslateUi

};

namespace Ui {
    class game_field: public Ui_game_field {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_FIELD_H
