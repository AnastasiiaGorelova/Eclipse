
#include<QApplication>
#include <QStyle>
#include "../include/game_window.h"



int main(int argc, char *argv[]) {

    size_t WIDTH = 800;
    size_t HEIGHT = 600;

    QApplication app(argc, argv);
    game_window window;
    window.resize(WIDTH, HEIGHT);
    window.setWindowTitle("Eclipse");

    window.show();
    return QApplication::exec();
}
