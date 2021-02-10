
#ifndef ECLIPSE_PROJECT_GAME_FWD_H
#define ECLIPSE_PROJECT_GAME_FWD_H

namespace eclipse {
struct Game;
static const int HEIGHT = 10;
static const int WIDTH = 50;
enum Game_state { ONGOING, FINISHED };
enum Field_state { ASTEROID, LIFE, SPACE_SHIP, NOTHING };

} // namespace eclipse

#endif // ECLIPSE_PROJECT_GAME_FWD_H
