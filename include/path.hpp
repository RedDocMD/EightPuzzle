#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "gameposition.hpp"

class Path {
  friend std::ostream &operator<<(std::ostream &os, const Path &path);

public:
  explicit Path() : nodes{}, distance{0}, heuristic{0} {}
  explicit Path(GamePosition &node, unsigned heuristic);
  bool add(std::shared_ptr<GamePosition> node, unsigned heuristic);
  bool operator<(const Path &other) const;
  std::shared_ptr<GamePosition> last() { return *(nodes.end() - 1); }

private:
  std::vector<std::shared_ptr<GamePosition>> nodes;
  unsigned distance;
  unsigned heuristic;
};

std::ostream &operator<<(std::ostream &os, const Path &path);