# 8 Puzzle

This solves the *8 puzzle* using A* star search algorithm. It uses the Manhattan distance heuristic.
The memory efficiency of the puzzle has been improved by using a `NodeStash` to store game state objects while the search algorithm itself stores only lists of pointers to the objects.

## Building
First clone this repo by running `git clone git@github.com:RedDocMD/EightPuzzle.git` or use the http version if you are behind a proxy network

Then make a `build` folder in the `EightPuzzle folder`
```
cd EightPuzzle
mkdir build
```

Then run `cmake` to generate build files and `make` to build the executable
```
cd build
cmake ..
make
```

The executable built is `eight_puzle`.

## Running
The solver is run as
```
./build/eight_puzzle <input-file>
```
Two example input files are provided in the `data` directory. The `0` in the file indicates an empty spot.

## Docker
Alternatively, this program can also be run as a [Docker](https://www.docker.com/) container.
```
docker run -it --rm redocmd/eight-puzzle:latest
root@570a7c96b22f:/usr/src/app/build# ./eight_puzzle ../data/solvable

```
