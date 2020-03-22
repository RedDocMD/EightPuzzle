#include "gameposition.hpp"

#include <random>
#include <unordered_set>

using namespace std;

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

  for (auto i = 0U; i < size; i++) {
    for (auto j = 0U; j < size; j++) {
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