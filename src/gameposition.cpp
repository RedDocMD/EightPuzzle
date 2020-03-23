#include "gameposition.hpp"

#include <cmath>
#include <exception>
#include <random>
#include <unordered_set>

using namespace std;

pair<unsigned, unsigned> find_position(GamePosition &node, int num);

GamePosition::GamePosition(unsigned size, NodeStash *stash) {
  this->size = size;
  this->board = vector<vector<int>>(size, vector<int>(size, 0));
  this->next = {};
  this->stash = stash;

  default_random_engine dre{};
  uniform_int_distribution<int> pos_gen(0, size * size - 1);
  uniform_int_distribution<int> num_gen(1, size * size - 1);
  unordered_set<int> done{};

  auto pos{pos_gen(dre)};
  auto posx{pos / size}, posy{pos % size};

  for (auto i{0U}; i < size; i++) {
    for (auto j{0U}; j < size; j++) {
      if (!(i == posx && j == posy)) {
        auto el{num_gen(dre)};
        while (done.find(el) != done.end())
          el = num_gen(dre);
        this->board[i][j] = el;
        done.insert(el);
      }
    }
  }
}

GamePosition::GamePosition(const GamePosition &game)
    : size{game.size}, board{game.board}, stash{game.stash} {
  next = vector<GamePosition *>();
  for (auto node : game.next)
    next.push_back(node);
}

GamePosition::GamePosition(GamePosition &&game) {
  size = game.size;
  board = std::move(game.board);
  next = std::move(game.next);
  stash = game.stash;

  game.size = 0;
  game.board = {};
  game.next = {};
  game.stash = nullptr;
}

GamePosition &GamePosition::operator=(const GamePosition &other) {
  size = other.size;
  board = other.board;
  next = vector<GamePosition *>();
  for (auto node : other.next)
    next.push_back(node);
  stash = other.stash;

  return *this;
}

GamePosition &GamePosition::operator=(GamePosition &&other) {
  size = other.size;
  board = std::move(other.board);
  next = std::move(other.next);
  stash = other.stash;

  other.size = 0;
  other.board = {};
  other.next = {};
  other.stash = nullptr;

  return *this;
}

bool GamePosition::operator==(const GamePosition &other) const {
  if (size != other.size)
    return false;
  for (auto i{0U}; i < size; i++) {
    for (auto j{0U}; j < size; j++) {
      if (board[i][j] != other.board[i][j])
        return false;
    }
  }
  return true;
}

void GamePosition::eval_next() {
  pair<int, int> empty_position;
  for (auto i{0U}; i < size; i++) {
    for (auto j{0U}; j < size; j++) {
      if (board[i][j] == 0) {
        empty_position = make_pair(i, j);
        break;
      }
    }
  }

  if (empty_position.first > 0) {
    auto new_next_board{board};
    new_next_board[empty_position.first][empty_position.second] =
        new_next_board[empty_position.first - 1][empty_position.second];
    new_next_board[empty_position.first - 1][empty_position.second] = 0;
    if (stash->check(new_next_board)) {
      next.push_back(stash->get(new_next_board).get());
    } else {
      auto node =
          make_unique<GamePosition>(GamePosition(new_next_board, stash));
      next.push_back(node.get());
      stash->push(new_next_board, node);
    }
  }

  if (empty_position.first < size - 1) {
    auto new_next_board{board};
    new_next_board[empty_position.first][empty_position.second] =
        new_next_board[empty_position.first + 1][empty_position.second];
    new_next_board[empty_position.first + 1][empty_position.second] = 0;
    if (stash->check(new_next_board)) {
      next.push_back(stash->get(new_next_board).get());
    } else {
      auto node =
          make_unique<GamePosition>(GamePosition(new_next_board, stash));
      next.push_back(node.get());
      stash->push(new_next_board, node);
    }
  }

  if (empty_position.second > 0) {
    auto new_next_board{board};
    new_next_board[empty_position.first][empty_position.second] =
        new_next_board[empty_position.first][empty_position.second - 1];
    new_next_board[empty_position.first][empty_position.second - 1] = 0;
    if (stash->check(new_next_board)) {
      next.push_back(stash->get(new_next_board).get());
    } else {
      auto node =
          make_unique<GamePosition>(GamePosition(new_next_board, stash));
      next.push_back(node.get());
      stash->push(new_next_board, node);
    }
  }

  if (empty_position.second < size - 1) {
    auto new_next_board{board};
    new_next_board[empty_position.first][empty_position.second] =
        new_next_board[empty_position.first][empty_position.second + 1];
    new_next_board[empty_position.first][empty_position.second + 1] = 0;
    if (stash->check(new_next_board)) {
      next.push_back(stash->get(new_next_board).get());
    } else {
      auto node =
          make_unique<GamePosition>(GamePosition(new_next_board, stash));
      next.push_back(node.get());
      stash->push(new_next_board, node);
    }
  }
}

unsigned heuristic(GamePosition &node, GamePosition &goal) {
  if (node.get_size() != goal.get_size())
    throw invalid_argument("GamePosition sizes don't match");
  auto sum{0U};
  for (auto i{0U}; i < node.get_size(); i++) {
    for (auto j{0U}; j < node.get_size(); j++) {
      auto goal_pos = find_position(goal, node[i][j]);
      sum += abs(static_cast<int>(i - goal_pos.first)) +
             abs(static_cast<int>(j - goal_pos.second));
    }
  }
  return sum;
}

pair<unsigned, unsigned> find_position(GamePosition &node, int num) {
  for (auto i{0U}; i < node.get_size(); i++) {
    for (auto j{0U}; j < node.get_size(); j++) {
      if (num == node[i][j])
        return make_pair(i, j);
    }
  }
  throw invalid_argument("Invalid GamePosition");
}

size_t GamePosition::hash() const {
  size_t sum{0U};
  for (auto p{0U}; p < size; p++)
    sum += sum * p + board[p / size][p % size];
  return sum;
}