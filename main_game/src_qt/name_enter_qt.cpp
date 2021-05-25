
#include "name_enter_qt.h"
#include "ui_name_enter_qt.h"
#include <QStyle>
#include <QDesktopWidget>
#include <QLabel>
#include <QGridLayout>
#include <iostream>
#include "God.h"

#define window_width 350
#define window_height 220
#define point_size 35

name_enter_qt::name_enter_qt(QWidget *parent) :
        QWidget(parent), ui(new Ui::name_enter_qt) {
    ui->setupUi(this);

    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                    (*this).size(),
                                    qApp->desktop()->availableGeometry()));

    ui->setupUi(this);
    QPixmap backgroung("../../images/menu_background.png"); //поменять картинку
    backgroung = backgroung.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, backgroung);
    this->setPalette(palette);

    auto *vlay = new QVBoxLayout(this);
    vlay->setAlignment(Qt::AlignCenter);

    QFont font;
    font.setWeight(QFont::ExtraBold); // set font weight with enum QFont::Weight
    font.setPixelSize(point_size); // this for setting font size

    auto text = new QLabel("Введите\n имя пользователя\n и нажмите enter\n");
    text->setParent(this);
    text->setStyleSheet("background-color: rgba(0,0,0,0%); color : white;");
    text->setFont(font);
    text->setAlignment(Qt::AlignCenter);
    vlay -> addWidget(text);

    echoLineEdit = new QLineEdit(this);
    echoLineEdit->setAlignment(Qt::AlignCenter);
    vlay->addWidget(echoLineEdit);

    connect(echoLineEdit, &QLineEdit::returnPressed, this, &name_enter_qt::_line_edit);

    vlay->setAlignment(Qt::AlignCenter);
    this->setLayout(vlay);

    setWindowTitle("Enter name");
    setFixedSize(window_width, window_height);
}

name_enter_qt::~name_enter_qt() {
    delete ui;
}

void name_enter_qt::_line_edit() {
    damn->name_entered((echoLineEdit->text()).toStdString());
}

void name_enter_qt::set_god(God* damn_) {
    damn = damn_;
}
