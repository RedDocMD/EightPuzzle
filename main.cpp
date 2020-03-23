#include <iostream>

#include "astar.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  cout << "Eight puzzle" << endl;
  vector<vector<int>> goal_board_eight{{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
  vector<vector<int>> start_board_eight{{1, 0, 4}, {2, 5, 3}, {8, 7, 6}};
  auto stash_eight = make_unique<NodeStash>(NodeStash());

  auto start_position_eight = make_unique<GamePosition>(
      GamePosition(start_board_eight, stash_eight.get()));
  auto goal_position_eight = make_unique<GamePosition>(
      GamePosition(goal_board_eight, stash_eight.get()));

  stash_eight->push(start_board_eight, start_position_eight);
  stash_eight->push(goal_board_eight, goal_position_eight);
  auto path_eight = astar_search(stash_eight->get(start_board_eight).get(),
                                 stash_eight->get(goal_board_eight).get());
  cout << path_eight << endl;
  return 0;
}
