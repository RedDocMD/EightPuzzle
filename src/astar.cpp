#include "astar.hpp"
#include <queue>
#include <unordered_set>

using namespace std;

Path astar_search(GamePosition *start, GamePosition *goal) {
  auto cmp = [](const shared_ptr<Path> &lhs, const shared_ptr<Path> &rhs) {
    return *lhs < *rhs;
  };
  priority_queue<shared_ptr<Path>, vector<shared_ptr<Path>>, decltype(cmp)>
      queue(cmp);
  unordered_set<GamePosition *, GamePositionPointerHash,
                GamePositionPointerEqual>
      done{};

  Path first{start, heuristic(*start, *goal)};
  queue.push(make_shared<Path>(first));

  while (!queue.empty()) {
    auto best = queue.top();
    queue.pop();

    auto last = best->last();
    if (done.find(last) != done.end())
      continue;

    last->eval_next();
    for (auto next : last->get_next()) {
      if (done.find(next.get()) != done.end())
        continue;
      auto new_path{*best};
      if (new_path.add(next, heuristic(*next, *goal))) {
        if (*next == *goal)
          return new_path;
        else
          queue.push(make_shared<Path>(new_path));
      }
    }
    done.insert(last);
  }
  return Path();
}