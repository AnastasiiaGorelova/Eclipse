
#include<QApplication>
#include <QStyle>
#include "../include/game_window.h"
#include "../include/God.h"

God damn;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    game_window window;
    return QApplication::exec();
}
