#include <iostream>

#include "astar.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  vector<vector<int>> goal_board_eight{{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
  vector<vector<int>> start_board_eight{{1, 0, 4}, {2, 5, 3}, {8, 7, 6}};
  auto stash = make_unique<NodeStash>(NodeStash());

  auto start_position =
      make_unique<GamePosition>(GamePosition(start_board_eight, stash.get()));
  auto goal_position =
      make_unique<GamePosition>(GamePosition(goal_board_eight, stash.get()));

  stash->push(start_board_eight, start_position);
  stash->push(goal_board_eight, goal_position);
  auto path = astar_search(stash->get(start_board_eight).get(),
                           stash->get(goal_board_eight).get());
  cout << path;
  return 0;
}
