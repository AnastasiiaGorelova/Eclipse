
#include "../include/game.h"
#include "../include/game_fwd.h"
#include <cmath>
#include <vector>
#include "include/asteroids_qt.h"

extern eclipse::Game *game;

namespace eclipse {

namespace {
void change_field() {}
// TODO
} // namespace

Game_state Game::get_game_state() const { return game_state; }

Field_state Game::get_field_state(int x, int y) const { return field[x][y]; }

int Game::get_time() const { return static_cast<int>(ceil(Game::time)); }

void Game::moving_asteroids() {
  // TODO
}

void Game::moving_shots() {
  // TODO
}

void Game::make_move() {
  // TODO
}

void Game::run_game() {
  // TODO
}

Game::Game() {
  field.resize(WIDTH, std::vector<Field_state>(HEIGHT, NOTHING));
  for (int i = my_ship.where_is_ship().first - my_ship.get_size();
       i <= my_ship.where_is_ship().first + my_ship.get_size(); i++) {
    for (int j = my_ship.where_is_ship().second - my_ship.get_size();
         j < HEIGHT; j++) {
      field[i][j] = SPACE_SHIP;
    }
  }
  time = static_cast<double>(clock()) / static_cast<double>(CLOCKS_PER_SEC);
}


//for qt
void Game::makeGame(int const width, int const height) {


  game->scene = new QGraphicsScene();
  ship = new eclipse::Space_ship();
  scene -> setSceneRect(0, 0, width, height);
  setScene(scene);
  scene->setBackgroundBrush(QBrush(QImage("../../images/background.jpeg")));
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setFixedSize(width, height);
  setWindowTitle("Eclipse");
  resize(width, height);
  ship->set_ship(ship->x, ship->y, ship->size);


        auto* present = new Asteroids_qt();
        Asteroid setting(present);
        setting.set_asteroid_in_field(setting.get_size());



        show();
}

} // namespace eclipse