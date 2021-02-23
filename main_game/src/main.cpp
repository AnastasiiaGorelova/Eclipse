
#include "../include/game.h"
#include "../include/game_fwd.h"
#include <iostream>

void print(eclipse::Game &g) {
    for (int j = 0; j < eclipse::HEIGHT; j++) {
        for (int i = 0; i < eclipse::WIDTH; i++) {
            if (g.get_field_state(i, j) == eclipse::NOTHING)
                std::cout << '.';
            else if (g.get_field_state(i, j) == eclipse::ASTEROID)
                std::cout << 'O';
            else if (g.get_field_state(i, j) == eclipse::SPACE_SHIP)
                std::cout << 'X';
            else if (g.get_field_state(i, j) == eclipse::SHOT)
                std::cout << 'S';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

int main() {
    eclipse::Game g;

    // only for debug
    std::cout << g.get_time() << '\n';
    print(g);
    while(g.get_game_state() != eclipse::FINISHED) {
        g.make_move(eclipse::RIGHT);
        print(g);
    }
    std::cout << g.get_time() << '\n';
    // finished

    return 0;
}
