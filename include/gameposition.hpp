#pragma once

#include <memory>
#include <vector>

class GamePosition {
public:
  explicit GamePosition(std::vector<std::vector<int>> board)
      : size{board.size()}, board{board}, next{} {}
  explicit GamePosition(unsigned size);
  explicit GamePosition(const GamePosition &game);
  explicit GamePosition(const GamePosition &&game);
  // TODO: Copy and move operators
  bool operator==(const GamePosition &other) const;
  void eval_next();
  unsigned get_size() const { return size; }

private:
  unsigned size;
  std::vector<std::vector<int>> board;
  std::vector<std::shared_ptr<GamePosition>> next;
};