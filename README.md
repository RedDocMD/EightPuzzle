# 8 Puzzle

This solves the *8 puzzle* using A* star search algorithm. It uses the Manhattan distance heuristic.
The memory efficiency of the puzzle has been improved by using a `NodeStash` to store game state objects while the search algorithm itself stores only lists of pointers to the objects.
