#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
struct Position {
    int x, y;
};

struct PlayerState {
    int id;
    Position pos;
};

enum PlayerAction {
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN,
};

class Game {
  private:
    std::vector<PlayerState *> players;

  public:
    bool setPlayerPosition(const Position &pos);
};

#endif
