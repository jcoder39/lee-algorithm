#include <iostream>
#include <random>
#include "../include/Lee.hpp"

int main() {
    using namespace name::bvv::Lee;

    const int dimension = 10;
    int matrix[dimension][dimension] = {
            {1, 1, 1, -1, 1, -1, 1, 1, -1, -1},
            {-1, 1, 1, 1, -1, 1, 1, -1, 1, 1},
            {-1, 1, -1, -1, 1, -1, 1, 1, -1, 1},
            {1, 1, 1, 1, 1, -1, -1, 1, -1, 1},
            {-1, -1, 1, -1, -1, -1, 1, 1, 1, 1},
            {-1, 1, 1, 1, 1, 1, -1, 1, 1, -1},
            {-1, 1, 1, 1, -1, 1, 1, -1, 1, -1},
            {1, -1, 1, 1, 1, 1, -1, 1, -1, 1},
            {1, -1, -1, -1, 1, 1, 1, -1, 1, 1},
            {1, -1, 1, 1, -1, 1, 1, 1, 1, 1}
    };

    int** map = new int*[dimension];
    for(int i = 0; i < dimension; i++){
        map[i] = new int[dimension];
    }
    for(int r = 0; r < dimension; r++){
        for(int c = 0; c < dimension; c++){
            map[r][c] = matrix[r][c];
        }
    }

    Grid grid(Size(0, 0, 9, 9));
    grid.SetFinderStrategy(new OrthogonalDiagonal());

//    grid.Init(map);
    grid.GenerateMapAndInit();

    std::cout << "Show cells code:" << std::endl;
    grid.DisplayGrid();

    std::cout << "Show values of cells:" << std::endl;
    grid.DisplayValuesOfCells();

//    std::cout << "Print neighbors" << std::endl;
//    grid.DisplayNeighbors();

    grid.SetStartCell("11");
    grid.SetGoalCell("88");

    grid.BuildPath();
    std::cout << "Show marks:" << std::endl;
    grid.DisplayMarks();

    Path path = grid.RestorePath();

    std::cout << std::endl;
    std::cout << "Path: ";
    for(auto& p : path._path){
        std::cout << p << ", ";
    }
    std::cout << std::endl;

    for(int i = 0; i < dimension; i++){
        delete[] map[i];
    }
    delete[] map;

    return 0;
}