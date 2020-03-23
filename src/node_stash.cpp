#include "gameposition.hpp"

using namespace std;

bool NodeStash::check(const std::vector<std::vector<int>> &board) const {
  return stash.find(board) != stash.end();
}

std::unique_ptr<GamePosition> &
NodeStash::get(const std::vector<std::vector<int>> &board) {
  return stash[board];
}

void NodeStash::push(std::vector<std::vector<int>> &board,
                     std::unique_ptr<GamePosition> &ptr) {
  stash[board] = unique_ptr<GamePosition>(move(ptr));
}