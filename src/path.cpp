#include "path.hpp"

using namespace std;

Path::Path(GamePosition &node, int heuristic) {
  this->nodes = {make_shared<GamePosition>(node)};
  this->distance = 0;
  this->heuristic = heuristic;
}

bool Path::add(std::shared_ptr<GamePosition> node, int heuristic) {
  for (auto old_node : nodes)
    if (old_node == node)
      return false;
  nodes.push_back(node);
  this->heuristic = heuristic;
  ++distance;
  return true;
}

std::ostream &Path::operator<<(std::ostream &os) const {
  os << "----------------------" << endl;
  for (auto node : nodes) {
    for (auto i{0U}; i < node->get_size(); i++) {
      for (auto j{0U}; j < node->get_size(); j++) {
        os << (*node)[i][j] << " ";
      }
      os << endl;
    }
  }
  os << "----------------------" << endl;
  return os;
}