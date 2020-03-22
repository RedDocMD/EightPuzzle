#pragma once

#include <memory>
#include <vector>

class GamePosition {
public:
  explicit GamePosition(std::vector<std::vector<int>> board)
      : size{board.size()}, board{board}, next{} {}
  explicit GamePosition(unsigned size);
  explicit GamePosition(const GamePosition &game)
      : size{game.size}, board{game.board}, next{game.next} {}
  explicit GamePosition(GamePosition &&game);
  GamePosition &operator=(const GamePosition &other);
  GamePosition &operator=(GamePosition &&other);
  bool operator==(const GamePosition &other) const;
  void eval_next();
  unsigned get_size() const { return size; }

private:
  unsigned long size;
  std::vector<std::vector<int>> board;
  std::vector<std::shared_ptr<GamePosition>> next;
};