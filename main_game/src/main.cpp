
#include "god.h"
#include <QApplication>

/*void print(eclipse::Game &game) {
    for (int j = 0; j < eclipse::kHeight; j++) {
        for (int i = 0; i < eclipse::kWidth; i++) {
            if (game.get_field_state(i, j) == eclipse::kNothing)
                std::cout << '.';
            else if (game.get_field_state(i, j) == eclipse::kAsteroid)
                std::cout << 'O';
            else if (game.get_field_state(i, j) == eclipse::kSpaceShip)
                std::cout << 'X';
            else if (game.get_field_state(i, j) == eclipse::kShot)
                std::cout << 'S';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}*/

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    God damn;
    damn.show_menu();
    return QApplication::exec();
}
