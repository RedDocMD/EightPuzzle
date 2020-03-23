#include "astar.hpp"
#include <queue>
#include <unordered_set>

using namespace std;

Path astar_search(GamePosition &start, GamePosition &goal) {
  priority_queue<Path> queue{};
  unordered_set<GamePosition *, GamePositionPointerHash,
                GamePositionPointerEqual>
      done{};

  Path first{&start, heuristic(start, goal)};
  queue.push(first);

  while (!queue.empty()) {
    auto best = queue.top();
    queue.pop();

    auto last = best.last();
    if (done.find(last) != done.end())
      continue;

    last->eval_next();
    for (auto next : last->get_next()) {
      if (done.find(next.get()) != done.end())
        continue;
      auto new_path{best};
      if (new_path.add(next.get(), heuristic(*next, goal))) {
        if (*next == goal)
          return new_path;
        else
          queue.push(new_path);
      }
    }
  }
  return Path{};
}