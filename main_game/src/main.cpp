
#include<QApplication>
#include <QStyle>
#include "../include/game_window.h"


eclipse::Game *game;

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    game_window window;
    window.resize(eclipse::WIDTH, eclipse::HEIGHT);
    window.setWindowTitle("Eclipse");

    window.show();
    return QApplication::exec();
}
