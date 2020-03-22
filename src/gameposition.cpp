#include "gameposition.hpp"

#include <cmath>
#include <exception>
#include <random>
#include <unordered_set>

using namespace std;

pair<unsigned, unsigned> find(GamePosition &node, int num);

GamePosition::GamePosition(unsigned size) {
  this->size = size;
  this->board = vector<vector<int>>(size, vector<int>(size, 0));
  this->next = {};

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

GamePosition::GamePosition(GamePosition &&game) {
  size = game.size;
  board = std::move(game.board);
  next = std::move(game.next);

  game.size = 0;
  game.board = {};
  game.next = {};
}

GamePosition &GamePosition::operator=(const GamePosition &other) {
  size = other.size;
  board = other.board;
  next = other.next;

  return *this;
}

GamePosition &GamePosition::operator=(GamePosition &&other) {
  size = other.size;
  board = std::move(other.board);
  next = std::move(other.next);

  other.size = 0;
  other.board = {};
  other.next = {};

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
    next.push_back(make_shared<GamePosition>(GamePosition(new_next_board)));
  }

  if (empty_position.first < size - 1) {
    auto new_next_board{board};
    new_next_board[empty_position.first][empty_position.second] =
        new_next_board[empty_position.first + 1][empty_position.second];
    new_next_board[empty_position.first + 1][empty_position.second] = 0;
    next.push_back(make_shared<GamePosition>(GamePosition(new_next_board)));
  }

  if (empty_position.second > 0) {
    auto new_next_board{board};
    new_next_board[empty_position.first][empty_position.second] =
        new_next_board[empty_position.first][empty_position.second - 1];
    new_next_board[empty_position.first][empty_position.second - 1] = 0;
    next.push_back(make_shared<GamePosition>(GamePosition(new_next_board)));
  }

  if (empty_position.second < size - 1) {
    auto new_next_board{board};
    new_next_board[empty_position.first][empty_position.second] =
        new_next_board[empty_position.first][empty_position.second + 1];
    new_next_board[empty_position.first][empty_position.second + 1] = 0;
    next.push_back(make_shared<GamePosition>(GamePosition(new_next_board)));
  }
}

unsigned heuristic(GamePosition &node, GamePosition &goal) {
  if (node.get_size() != goal.get_size())
    throw invalid_argument("GamePosition sizes don't match");
  auto sum{0U};
  for (auto i{0U}; i < node.get_size(); i++) {
    for (auto j{0U}; j < node.get_size(); j++) {
      auto goal_pos = find(goal, node[i][j]);
      sum += abs(static_cast<int>(i - goal_pos.first)) +
             abs(static_cast<int>(j - goal_pos.second));
    }
  }
  return sum;
}

pair<unsigned, unsigned> find(GamePosition &node, int num) {
  for (auto i{0U}; i < node.get_size(); i++) {
    for (auto j{0U}; j < node.get_size(); j++) {
      if (num == node[i][j])
        return make_pair(i, j);
    }
  }
  throw invalid_argument("Invalid GamePosition");
}