
#include "../include/game.h"
#include "../include/game_fwd.h"
#include <cmath>
#include <vector>

namespace eclipse {
    namespace {
        void change_field() {}
        // TODO
    }// namespace

    Game_state Game::get_game_state() const { return game_state; }

    Field_state Game::get_field_state(int x, int y) const { return field[x][y]; }

    int Game::get_time() const { return static_cast<int>(ceil(Game::time)); }

    void Game::moving_asteroids() {
        //TODO
    }

    void Game::moving_shots() {
        //TODO
    }

    void Game::make_move() {
        //TODO
    }

    void Game::run_game() {
        //TODO
    }


}// namespace eclipse