#include <iostream>
#include <stack>
#include <random>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
#include <ctime>

#define Maze_Max_Size 100
#define PATH 0
#define WALL 1
#define SOLVE_PATH 2
#define EXPLORED_PATH 3
#define WORMHOLE1 4
#define WORMHOLE2 5
#define SHORTEST_PATH 6

struct Index {
    int x;
    int y;
};
Index Worm1;
Index Worm2;

int height, width;
int maze_data[Maze_Max_Size][Maze_Max_Size] = {};
int wormholeX1, wormholeY1, wormholeX2, wormholeY2;

std::stack<Index> myStack;

int dx[4] = {0, 1, 0, -1}; // Directions: Up, Right, Down, Left
int dy[4] = {-1, 0, 1, 0};

void PrintMaze() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (maze_data[i][j] == WALL)
                std::cout << "⬜️";
            else if (maze_data[i][j] == PATH)
                std::cout << "　";
            else if (maze_data[i][j] == SOLVE_PATH)
                std::cout << "🔹";
            else if (maze_data[i][j] == EXPLORED_PATH)
                std::cout << "🔸";
            else if (maze_data[i][j] == WORMHOLE1)
                std::cout << "🟡";
            else if (maze_data[i][j] == WORMHOLE2)
                std::cout << "🟡";
            else if (maze_data[i][j] == SHORTEST_PATH)
                std::cout << "🟢"; // choose an appropriate symbol or emoji

            
        }
        std::cout << std::endl;
    }
}

// Function to generate the maze
void GenerateMaze() {
    std::random_device rd;      // To obtain a seed for the random number engine
    std::mt19937 rng(rd());     // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<int> dist(0, 3);  // Uniform distribution

    // Initialize maze as a grid of walls
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            maze_data[i][j] = WALL;
        }
    }

    // Choose random starting point and mark it as a path
    int startX = 1;
    int startY = 1;
    maze_data[startX][startY] = PATH;

    // Create a stack to store visited cells
    myStack.push({startX, startY});

    while (!myStack.empty()) {
        // Perform DFS to generate maze
        Index current = myStack.top();
        myStack.pop();

        int x = current.x;
        int y = current.y;

        // Shuffle the directions
        std::vector<int> directions = {0, 1, 2, 3};
        std::shuffle(directions.begin(), directions.end(), rng);

        // Try to move in each direction
        for (int d : directions) {
            int newX = x + dx[d] * 2;
            int newY = y + dy[d] * 2;

            // If new position is within maze boundaries and is a wall, break the wall and mark as a path
            if (newX >= 1 && newX < height - 1 && newY >= 1 && newY < width - 1 && maze_data[newX][newY] == WALL) {
                // Break the wall
                maze_data[x + dx[d]][y + dy[d]] = PATH;
                maze_data[newX][newY] = PATH;

                // Push the next cell to the stack
                myStack.push({newX, newY});
            }
        }
    }

    // Generate random positions for the wormhole ends
    std::srand(std::time(nullptr));
    
    // Make sure the wormhole ends are on the path and not the same cell
    do {
        wormholeX1 = std::rand() % (height - 2) + 1;
        wormholeY1 = std::rand() % (width - 2) + 1;
    } while (maze_data[wormholeX1][wormholeY1] != PATH);
    do {
        wormholeX2 = std::rand() % (height - 2) + 1;
        wormholeY2 = std::rand() % (width - 2) + 1;
    } while (maze_data[wormholeX2][wormholeY2] != PATH || (wormholeX1 == wormholeX2 && wormholeY1 == wormholeY2));

    // Mark the wormhole ends
    maze_data[wormholeX1][wormholeY1] = WORMHOLE1; // Let's use WORMHOLE to represent the wormhole ends
    maze_data[wormholeX2][wormholeY2] = WORMHOLE2;
    Worm1 = {wormholeX1,wormholeY1};
    Worm2 = {wormholeX2,wormholeY2};
}

// Function to solve the maze using BFS
void SolveMaze() {
    // Initialize BFS queue and visited array
    std::queue<Index> bfsQueue;                             // Queue for BFS
    bool visited[Maze_Max_Size][Maze_Max_Size] = {false};   // Visited array
    Index previous[Maze_Max_Size][Maze_Max_Size];           // Array to store previous cell

    // Find the wormhole ends
    std::vector<Index> wormholes;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (maze_data[i][j] == WORMHOLE1 || maze_data[i][j] == WORMHOLE2) {
                wormholes.push_back({i, j});
            }
        }
    }

    // Start from the first path cell (1, 1)
    bfsQueue.push({1, 1});
    visited[1][1] = true;

    while (!bfsQueue.empty()) {
        // Perform BFS to find shortest path
        Index current = bfsQueue.front();
        bfsQueue.pop();

        // Try to move in each direction
        for (int d = 0; d < 4; d++) {
            int newX = current.x + dx[d];
            int newY = current.y + dy[d];

            // If the new cell is a path and hasn't been visited yet, visit it
            if (newX >= 0 && newX < height && newY >= 0 && newY < width && !visited[newX][newY]) {
                // If the new cell is a wormhole end, teleport to the other end
                if (maze_data[newX][newY] == WORMHOLE1 || maze_data[newX][newY] == WORMHOLE2) {
                    Index otherEnd = maze_data[newX][newY] == WORMHOLE1 ? wormholes[1] : wormholes[0];

                    if (!visited[otherEnd.x][otherEnd.y]) {
                        // Mark the cell as visited and add it to the queue
                        bfsQueue.push({otherEnd.x, otherEnd.y});
                        visited[otherEnd.x][otherEnd.y] = true;
                        // Store the previous cell
                        previous[otherEnd.x][otherEnd.y] = current;
                    }

                    // Mark the cell as explored path
                    maze_data[newX][newY] = EXPLORED_PATH;
                    maze_data[otherEnd.x][otherEnd.y] = EXPLORED_PATH;
                    
                } else if (maze_data[newX][newY] == PATH) {
                    bfsQueue.push({newX, newY});
                    visited[newX][newY] = true;
                    previous[newX][newY] = current;

                    // Mark the cell as explored path
                    maze_data[newX][newY] = EXPLORED_PATH;

                    // If we reached the end of the maze (height-2, width-2), reconstruct the shortest path and return
                    if (newX == height - 2 && newY == width - 2) {
                        Index cell = {height - 2, width - 2};
                        while (cell.x != 1 || cell.y != 1) {
                            maze_data[cell.x][cell.y] = SHORTEST_PATH;
                            cell = previous[cell.x][cell.y];
                        }
                        maze_data[1][1] = SHORTEST_PATH; // Mark the start cell as part of the solution
                    }
                }
            }
        }
    }
}


int main() {
    int flag = 0;
    while(flag!=1){
        std::cout << "Enter the size of the maze (odd numbers only): ";
        std::cin >> height;

        width = height;

        GenerateMaze();

        std::cout << "Maze:" << std::endl;
        PrintMaze();

        std::cout << std::endl;

        SolveMaze();

        maze_data[Worm1.x][Worm1.y] = WORMHOLE1; 
        maze_data[Worm2.x][Worm2.y] = WORMHOLE2; 

        std::cout << "Solved Maze:" << std::endl;
        PrintMaze();
        std::cout << "0 to continue, 1 to exit" << std::endl;
        std::cin >> flag;
    }

    return 0;
}

