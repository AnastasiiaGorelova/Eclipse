#ifndef MAIN_GAME_GAME_H
#define MAIN_GAME_GAME_H

#include <random>
#include <string>
#include <utility>
#include <vector>
#include "asteroids.h"
#include "game_fwd.h"
#include "shots.h"
#include "space_ship.h"

// TODO: подключить таймер, функции запуска игры, почистить и потестить код

namespace eclipse {
struct Changes {
    std::string id;
    int size;
    std::string object_name;
    std::pair<int, int> new_coordinates;

    Changes(std::string id,
            int size,
            std::string object_name,
            std::pair<int, int> new_)
        : id(std::move(id)),
          size(size),
          object_name(std::move(object_name)),
          new_coordinates(std::move(new_)) {
    }
};

struct Game {
private:
    GameState game_state = kOngoing;
    std::vector<std::vector<FieldState>> field;
    spaceship ship = spaceship(kWidth, kHeight);
    int lives = 3;
    int asteroids_speed = 2;
    std::vector<Asteroid> asteroids_in_the_field;
    std::vector<Shot> shots_in_the_field;

    void change_field(int x_start,
                      int x_finish,
                      int y_start,
                      int y_finish,
                      FieldState value);
    void check_for_living();
    void shoot();
    void generate_asteroid();
    void moving_shots();
    void moving_asteroids();
    void moving_ship(MoveDirection direction);

public:
    Game() {
        field.resize(kWidth, std::vector<FieldState>(kHeight, kNothing));
        for (int i = ship.get_coordinates().first;
             i < ship.get_coordinates().first + ship.get_size(); i++) {
            for (int j = ship.get_coordinates().second; j < kHeight; j++) {
                field[i][j] = kSpaceShip;
            }
        }
    }

    std::vector<Changes> changes = {Changes(ship.get_id(),
                                            ship.get_size(),
                                            "ship",
                                            ship.get_coordinates())};

    GameState get_game_state() const;

    FieldState get_field_state(int x, int y) const;

    void make_move(MoveDirection direction = kNoMove);
};

}  // namespace eclipse

#endif  // MAIN_GAME_GAME_H
