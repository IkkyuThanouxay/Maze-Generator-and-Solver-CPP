# Maze Solver

This program generates a maze using a depth-first search (DFS) algorithm and solves it using a breadth-first search (BFS) algorithm. The maze is represented as a grid, where `⬜️` represents walls, `　` represents paths, and various symbols are used to indicate different states during the solving process.

## Program Structure

- The program is written in C++.
- It uses the following libraries:
    - `<iostream>`: For input/output operations.
    - `<stack>`: For implementing the DFS algorithm.
    - `<random>`: For generating random numbers.
    - `<algorithm>`: For shuffling directions.
    - `<vector>`: For storing directions and wormhole ends.
    - `<queue>`: For implementing the BFS algorithm.
    - `<tuple>`: For storing previous cell information.
    - `<ctime>`: For generating random positions.
- Constants:
    - `Maze_Max_Size`: Maximum size of the maze grid.
    - `PATH`, `WALL`, `SOLVE_PATH`, `EXPLORED_PATH`, `WORMHOLE1`, `WORMHOLE2`, `SHORTEST_PATH`: Numeric representations of different states in the maze.
- Structures:
    - `Index`: Structure to store the x and y coordinates of a cell.
- Global Variables:
    - `height`, `width`: Dimensions of the maze.
    - `maze_data[Maze_Max_Size][Maze_Max_Size]`: 2D array to store the maze grid.
    - `wormholeX1`, `wormholeY1`, `wormholeX2`, `wormholeY2`: Variables to store the positions of the wormhole ends.
    - `myStack`: Stack data structure used for DFS.
    - `dx[4]`, `dy[4]`: Arrays representing the four cardinal directions.
    - `Worm1`, `Worm2`: Structures to store the positions of the wormhole ends.
- Functions:
    - `PrintMaze()`: Prints the maze grid with appropriate symbols for each state.
    - `GenerateMaze()`: Generates a random maze using the DFS algorithm.
    - `SolveMaze()`: Solves the generated maze using the BFS algorithm.

## Usage

1. The program prompts you to enter the size of the maze. Only odd numbers are allowed.
2. It generates a maze using the DFS algorithm and displays the initial maze grid.
3. The maze is solved using the BFS algorithm, and the solved maze grid is displayed.
4. You can continue generating and solving mazes by entering `0`, or you can exit the program by entering `1`.

Feel free to modify and experiment with the code according to your needs.
