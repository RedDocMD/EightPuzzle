#include <iostream>
#include <fstream>

#include "astar.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  if (argc != 2)  {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }
  auto filename = string(argv[1]);
  ifstream inp(filename);

  cout << "Eight puzzle" << endl;

  vector<vector<int>> goal_board_eight{{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
  vector<vector<int>> start_board_eight(3, vector<int>(3));
  for (auto &row : start_board_eight) {
    for (auto &el : row) {
      inp >> el;
    }
  }
  inp.close();

  auto stash_eight = make_unique<NodeStash>(NodeStash());

  auto start_position_eight = make_unique<GamePosition>(
      GamePosition(start_board_eight, stash_eight.get()));
  auto goal_position_eight = make_unique<GamePosition>(
      GamePosition(goal_board_eight, stash_eight.get()));

  stash_eight->push(start_board_eight, start_position_eight);
  stash_eight->push(goal_board_eight, goal_position_eight);
  auto path_eight = astar_search(stash_eight->get(start_board_eight).get(),
                                 stash_eight->get(goal_board_eight).get());

  if (path_eight.size()) {
    cout << path_eight << endl;
    cout << "Solved in " << path_eight.size() - 1 << " moves" << endl;
  } else {
    cout << "Unsolvable board position." << endl;
  }

  return 0;
}
