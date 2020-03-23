#include "path.hpp"

using namespace std;

Path::Path(GamePosition *node, unsigned heuristic) {
  this->nodes = vector<GamePosition *>();
  (this->nodes).push_back(node);
  this->distance = 0;
  this->heuristic = heuristic;
}

bool Path::add(GamePosition *node, unsigned heuristic) {
  for (auto old_node : nodes)
    if (old_node == node)
      return false;
  nodes.push_back(node);
  this->heuristic = heuristic;
  ++distance;
  return true;
}

std::ostream &operator<<(std::ostream &os, const Path &path) {
  os << "----------------------" << endl;
  for (auto node : path.nodes) {
    for (auto i{0U}; i < node->get_size(); i++) {
      for (auto j{0U}; j < node->get_size(); j++) {
        os << (*node)[i][j] << " ";
      }
      os << endl;
    }
    os << endl;
  }
  os << "----------------------" << endl;
  return os;
}

bool Path::operator<(const Path &other) const {
  return (distance + heuristic) > (other.distance + other.heuristic);
}