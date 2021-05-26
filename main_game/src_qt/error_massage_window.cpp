
#include <QVBoxLayout>
#include <QLabel>
#include "error_massage_window.h"
#include "ui_error_massage_window.h"
#include <QStyle>
#include <QDesktopWidget>
#include "god.h"

#define window_width 400
#define window_height 300
#define point_size 25

error_massage_window::error_massage_window(QWidget *parent) :
        QWidget(parent), ui(new Ui::error_massage_window) {
    ui->setupUi(this);

    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                    (*this).size(),
                                    qApp->desktop()->availableGeometry()));

    setWindowTitle("Error");
    setFixedSize(window_width, window_height);

    setWindowFlags(Qt::WindowMinimizeButtonHint);

    QPixmap backgroung("../../images/menu_background.png");
    backgroung = backgroung.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, backgroung);
    this->setPalette(palette);
}

error_massage_window::~error_massage_window() {
    delete ui;
}

void error_massage_window::arduino_setting_error() {
    auto *vlay = new QVBoxLayout(this);
    vlay->setAlignment(Qt::AlignCenter);

    QFont font;
    font.setWeight(QFont::ExtraBold);
    font.setPixelSize(point_size);

    auto text = new QLabel("Ардуино не подключено.\n Проверьте соединение\n или выберите другой\n режим управления\n");
    text->setParent(this);
    text->setStyleSheet("background-color: rgba(0,0,0,0%); color : white;");
    text->setFont(font);
    text->setAlignment(Qt::AlignCenter);
    vlay -> addWidget(text);

    QString style = "QPushButton{border: 1px solid transparent;text-align: center;"
                    "color:rgba(255,255,255,255);"
                    "border-radius: 8px;"
                    "border-width: 3px;"
                    "border-image: 9,2,5,2; "
                    "background-position: top left;"
                    "background-origin: content;"
                    "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
                    "stop:0 rgba(200, 110, 100, 200), stop:1 rgba(130, 148, 130, 200));}"
                    "QPushButton::chunk {background-color: qlineargradient(x1: 0, y1: 0, "
                    "x2: 0, y2: 1, stop: 0 rgba(255,200,0,255), stop: 1 "
                    "rgba(255,0,0,255));}"
                    "QPushButton{border-color:qlineargradient(spread:pad, x1:0, y1:0, "
                    "x2:1, y2:1, stop:0 rgba(255, 200, 200, 200), stop:1 rgba(255, 200, "
                    "200, 200));}";

    back_to_selection_window = new QPushButton("Вернуться к выбору контроллера");
    back_to_selection_window->setParent(this);
    back_to_selection_window->setStyleSheet(style);
    vlay->addWidget(back_to_selection_window);

    connect(back_to_selection_window, &QPushButton::released, this, &error_massage_window::_on_back_to_menu_clicked);

    this->setLayout(vlay);
}

void error_massage_window::_on_back_to_menu_clicked() {
    damn->close_error_massage_window();
    damn->show_selection_window();
}

void error_massage_window::set_god(God *damn_) {
    damn = damn_;
}
