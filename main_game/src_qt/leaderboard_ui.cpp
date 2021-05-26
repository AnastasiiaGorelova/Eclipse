
#include <QHBoxLayout>
#include "leaderboard_ui.h"
#include "ui_local_leaderboard_ui.h"
#include <QDesktopWidget>
#include <QHeaderView>
#include <fstream>
#include <iostream>

#define window_width 400
#define window_height 325
#define row_count 10
#define column_count 2
#define point_size 20
#define column_width 180

local_leaderboard_ui::local_leaderboard_ui(QWidget *parent) :
        QWidget(parent), ui(new Ui::local_leaderboard_ui) {
    ui->setupUi(this);

    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                    (*this).size(),
                                    qApp->desktop()->availableGeometry()));

    setFixedSize(window_width, window_height);
    setWindowTitle("Score table");

    QPixmap backgroung("../../images/background_leaderboard.png");  //поменять картинку
    backgroung = backgroung.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, backgroung);
    this->setPalette(palette);

    table = new QTableWidget;
    table->setStyleSheet("QTableWidget {background-color: transparent;}");
    table->horizontalHeader()->hide();
    table->verticalHeader()->hide();
    table->horizontalHeader()->setVisible(false);
    table->verticalHeader()->setVisible(false);
    table->setRowCount(row_count);
    table->setColumnCount(column_count);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->resizeSection(0, column_width);
    table->horizontalHeader()->resizeSection(1, column_width);
    table->setFocusPolicy(Qt::NoFocus);

    auto fnt = table->font();
    fnt.setPointSize(point_size);
    table->setFont(fnt);
}

local_leaderboard_ui::~local_leaderboard_ui() {
    delete table;
    delete ui;
}

void local_leaderboard_ui::download_local_leaderboard() {
    std::ifstream in("LocalLeaderBoard.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        int row = 0;
        std::string line;
        std::string score;
        while (getline(in, line, ' '))
        {
            getline(in, score);
            auto *item_1 = new QTableWidgetItem(QString::fromStdString(line));
            auto *item_2 = new QTableWidgetItem(QString::fromStdString(score));
            item_1->setFlags(Qt::ItemIsEnabled);
            item_2->setFlags(Qt::ItemIsEnabled);
            item_1->setTextColor(QColor(255, 255, 255));
            item_2->setTextColor(QColor(255, 255, 255));
            item_1->setTextAlignment(Qt::AlignCenter);
            item_2->setTextAlignment(Qt::AlignCenter);
            table->setItem(row, 0, item_1);
            table->setItem(row, 1, item_2);
            row++;
        }
        int x = row;
        for (; row < 10; row++) {
            table->removeRow(x);
        }
        in.close();
    } else {
        std::cerr << "File doesn't exist";
    }

    auto *layout = new QHBoxLayout(this);
    layout->addWidget(table);
    setLayout(layout);
}

void local_leaderboard_ui::download_server_leaderboard() {

}
