#include<QApplication>
#include "../include/God.h"

game_window *menu;
main_window *game_view;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    God::show_menu();
    return QApplication::exec();
}
