#include <iostream>

#include "astar.hpp"
#include "gameposition.hpp"
#include "path.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  vector<vector<int>> goal_board_eight{{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
  vector<vector<int>> start_board_eight{{1, 0, 4}, {2, 5, 3}, {8, 7, 6}};
  GamePosition start_position(start_board_eight);
  GamePosition goal_position(goal_board_eight);
  auto path = astar_search(start_position, goal_position);
  cout << path;
  return 0;
}
