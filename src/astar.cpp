#include "astar.hpp"
#include <queue>
#include <unordered_set>

using namespace std;

Path astar_search(GamePosition &start, GamePosition &goal) {
  priority_queue<Path> queue{};
  unordered_set<shared_ptr<GamePosition>, GamePositionPointerHash,
                GamePositionPointerEqual>
      done{};

  queue.push(Path{start, heuristic(start, goal)});

  while (!queue.empty()) {
    auto best = queue.top();
    queue.pop();

    auto last = best.last();
    if (done.find(last) != done.end())
      continue;

    last->eval_next();
    for (auto next : last->get_next()) {
      if (done.find(next) != done.end())
        continue;
      auto new_path{best};
      if (new_path.add(next, heuristic(*next, goal))) {
        if (*next == goal)
          return new_path;
        else
          queue.push(new_path);
      }
    }
  }
  return Path{};
}