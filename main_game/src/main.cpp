#include "game.h"
#include "game_fwd.h"
#include <iostream>
#include <thread>
#include <mutex>

#include <Modification_store.h>

#include "God.h"
#include <QApplication>

God damn;
Modification_store train;
std::mutex m;

void print(eclipse::Game &game) {
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
}

int main(int argc, char *argv[]) {
    //m.lock();
    QApplication app(argc, argv);
    damn.show_menu();
    damn.clicked_on_start();
    //damn.show_game_field();
    //eclipse::Game game;

    //может не в main будем создавать, а из боженьки? вдруг несколько сессий игры понадобится
//    std::thread thread([&]() {
//        while (damn.game->get_game_state() != eclipse::kFinished) {
//            std::this_thread::sleep_for(std::chrono::milliseconds(500));
//            damn.make_move_in_logic();
//        }
//    });
//    damn.make_changes_in_qt();


    // only for debug
    //print(game);
    //    while (game.get_game_state() != eclipse::kFinished) {
    //        game.make_move(eclipse::kLeft);
    //        print(game);
    //    }
    //    print(game);
    // finished

    return QApplication::exec();
}
