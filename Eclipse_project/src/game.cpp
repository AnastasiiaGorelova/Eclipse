
#include "../include/game.h"
#include "../include/game_fwd.h"
#include <cmath>
#include <vector>

namespace eclipse {
namespace {
// TODO
}

Game_state Game::get_game_state() const { return game_state; }

Field_state Game::get_field_state(int x, int y) const { return field[x][y]; }

int Game::get_time() const { return static_cast<int>(ceil(Game::time)); }

} // namespace eclipse
