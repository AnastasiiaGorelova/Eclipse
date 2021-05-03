//
// Created by alena on 03.05.2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_name_enter_qt.h" resolved

#include "name_enter_qt.h"
#include "ui_name_enter_qt.h"

name_enter_qt::name_enter_qt(QWidget *parent) :
        QWidget(parent), ui(new Ui::name_enter_qt) {
    ui->setupUi(this);
}

name_enter_qt::~name_enter_qt() {
    delete ui;
}
