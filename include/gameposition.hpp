#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

class NodeStash;

class GamePosition {
public:
  GamePosition(std::vector<std::vector<int>> &board, NodeStash *stash)
      : size{board.size()}, board{board}, next{}, stash{stash} {}
  GamePosition(unsigned size, NodeStash *stash);
  GamePosition(const GamePosition &game);
  GamePosition(GamePosition &&game);
  ~GamePosition() = default;
  GamePosition &operator=(const GamePosition &other);
  GamePosition &operator=(GamePosition &&other);
  bool operator==(const GamePosition &other) const;
  std::vector<int> &operator[](unsigned int pos) { return board[pos]; }
  void eval_next();
  unsigned get_size() const { return size; }
  std::size_t hash() const;
  std::vector<GamePosition *> &get_next() { return next; }

private:
  unsigned long size;
  std::vector<std::vector<int>> board;
  std::vector<GamePosition *> next;
  NodeStash *stash;
};

unsigned heuristic(GamePosition &node, GamePosition &goal);

struct GamePositionPointerHash {
  std::size_t operator()(const GamePosition *node) const {
    return node->hash();
  }
};

struct GamePositionPointerEqual {
  bool operator()(const GamePosition *lhs, const GamePosition *rhs) const {
    return *lhs == *rhs;
  }
};

struct BoardHash {
  std::size_t operator()(const std::vector<std::vector<int>> &board) const {
    size_t sum{0U};
    auto size{board.size()};
    for (auto p{0U}; p < size; p++)
      sum += sum * p + board[p / size][p % size];
    return sum;
  }
};

class NodeStash {
public:
  bool check(const std::vector<std::vector<int>> &board) const;
  std::unique_ptr<GamePosition> &
  get(const std::vector<std::vector<int>> &board);
  void push(std::vector<std::vector<int>> &board,
            std::unique_ptr<GamePosition> &ptr);

private:
  std::unordered_map<std::vector<std::vector<int>>,
                     std::unique_ptr<GamePosition>, BoardHash>
      stash;
};
