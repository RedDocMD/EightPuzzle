#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "gameposition.hpp"

class Path {
public:
  explicit Path() : nodes{}, distance{0}, heuristic{0} {}
  explicit Path(GamePosition &node, int heuristic);
  bool add(std::shared_ptr<GamePosition> node, int heuristic);
  std::ostream &operator<<(std::ostream &os) const;

private:
  std::vector<std::shared_ptr<GamePosition>> nodes;
  unsigned distance;
  unsigned heuristic;
};