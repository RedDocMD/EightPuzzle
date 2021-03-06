#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "gameposition.hpp"

class Path {
  friend std::ostream &operator<<(std::ostream &os, const Path &path);

public:
  Path() : nodes{}, distance{0}, heuristic{0} {}
  Path(const Path &path);
  Path(Path &&path);
  ~Path() = default;
  explicit Path(GamePosition *node, unsigned heuristic);
  bool add(GamePosition *node, unsigned heuristic);
  bool operator<(const Path &other) const;
  Path &operator=(const Path &path);
  Path &operator=(Path &&path);
  GamePosition *last() { return *(nodes.end() - 1); }
  size_t size() const { return nodes.size(); }

private:
  std::vector<GamePosition *> nodes;
  unsigned distance;
  unsigned heuristic;
};

std::ostream &operator<<(std::ostream &os, const Path &path);