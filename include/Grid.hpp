//
// Created by slavik on 4/19/17.
//

#ifndef LEE_GRID_HPP
#define LEE_GRID_HPP

#include <string>
#include <map>
#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <ctime>
#include "Lee.hpp"

class Grid
{
public:
    explicit Grid(const Size& size) : _size(size), _startCell(nullptr), _goalCell(nullptr), _mark(0), _strategy(new Orthogonal) {}

    void Init(int** map)
    {
        for(int r = _size._x; r <= _size._width; r++){
            for(int c = _size._y; c <= _size._height; c++){
                auto cell = std::shared_ptr<Cell>(new Cell(Point(r, c), map[r][c]));
                _cells.insert({cell->GetCode(), cell});
            }
        }

        _strategy->CreateRelations(_size, _cells);
    }

    void GenerateMapAndInit()
    {
        std::mt19937 rng(time(0));
        std::uniform_int_distribution<int> uni(1, 3);

        for(int r = _size._x; r <= _size._width; r++){
            for(int c = _size._y; c <= _size._height; c++){
                int value = uni(rng);
                if(value == 3){
                    value = IMPASSABLE;
                } else if(value < 3){
                    value = PASSABLE;
                }
                auto cell = std::shared_ptr<Cell>(new Cell(Point(r, c), value));
                _cells.insert({cell->GetCode(), cell});
            }
        }

        _strategy->CreateRelations(_size, _cells);
    }

    void BuildPath()
    {
        _startCell = _cells.at(_startCellCode).get();
        _startCell->SetMark(_mark);
        _goalCell = _cells.at(_goalCellCode).get();
        auto& neighbors = _startCell->GetNeighbors();
        _cellsInWork.reserve(neighbors.size());
        std::copy(neighbors.begin(), neighbors.end(), std::back_inserter(_cellsInWork));

        std::vector<Cell*> temp;
        do {
            if(_goalCell->isMarked()){
                break;
            }
            _mark++;
            temp.clear();
            temp.reserve(50);
            for(auto neighbor : _cellsInWork){
                if(neighbor->isMarked()){
                    continue;
                }
                if(neighbor->GetValue() == IMPASSABLE){
                    neighbor->SetMark(IMPASSABLE);
                    continue;
                }
                neighbor->SetMark(_mark);
                auto& neighborsOfNeighbor = neighbor->GetNeighbors();
                std::copy(neighborsOfNeighbor.begin(), neighborsOfNeighbor.end(), std::back_inserter(temp));
            }
            _cellsInWork.clear();
            _cellsInWork.reserve(temp.size());
            std::copy(temp.begin(), temp.end(), std::back_inserter(_cellsInWork));
        } while(true);
    }

    void Reset()
    {
        _cells.clear();
        _cellsInWork.clear();
        _mark = 0;
        _strategy = std::shared_ptr<Strategy>(new Orthogonal);
    }

    void SetFinderStrategy(Strategy* strategy)
    {
        _strategy = std::shared_ptr<Strategy>(strategy);
    }

    Path RestorePath()
    {
        std::vector<std::string> path;
        Cell* current = _goalCell;
        path.push_back(current->GetCode());
        Path::Status status = Path::OK;
        do {
            if(current == _startCell){
                break;
            }
            current = current->GetNeighborWithMinMark();
            if(current == nullptr){
                status = Path::WRONG_PATH;
                break;
            }
            path.push_back(current->GetCode());
        } while(true);

        return Path(status, path);
    }

    void SetStartCell(const std::string& code)
    {
        _startCellCode = code;
    }

    void SetGoalCell(const std::string& code)
    {
        _goalCellCode = code;
    }

    void DisplayGrid()
    {
        std::cout << "  ";
        for(int c = _size._y; c <= _size._height; c++){
            std::cout << c << "  ";
        }
        std::cout << std::endl;
        std::cout << " _";
        for(int c = _size._y; c <= _size._height * 3; c++){
            std::cout << "_";
        }
        std::cout << std::endl;
        for(int r = _size._x; r <= _size._width; r++){
            std::cout << r << "|";
            for(int c = _size._y; c <= _size._height; c++){
                std::string code = getCode(r, c);
                auto& cell = _cells.at(code);
                std::cout << " " << cell->GetCode();
            }
            std::cout << std::endl;
        }
    }

    void DisplayValuesOfCells()
    {
        std::cout << "   ";
        for(int c = _size._y; c <= _size._height; c++){
            std::cout << c << " ";
        }
        std::cout << std::endl;
        std::cout << " _";
        for(int c = _size._y; c <= _size._height * 2; c++){
            std::cout << "_";
        }
        std::cout << std::endl;
        for(int r = _size._x; r <= _size._width; r++){
            std::cout << r << "|";
            for(int c = _size._y; c <= _size._height; c++){
                std::string code = getCode(r, c);
                auto& cell = _cells.at(code);
                std::cout << " " << cell->GetValue();
            }
            std::cout << std::endl;
        }
    }

    void DisplayMarks()
    {
        std::cout << "   ";
        for(int c = _size._y; c <= _size._height; c++){
            std::cout << c << " ";
        }
        std::cout << std::endl;
        std::cout << " _";
        for(int c = _size._y; c <= _size._height * 2; c++){
            std::cout << "_";
        }
        std::cout << std::endl;
        for(int r = _size._x; r <= _size._width; r++){
            std::cout << r << "|";
            for(int c = _size._y; c <= _size._height; c++){
                std::string code = getCode(r, c);
                auto& cell = _cells.at(code);
                std::cout << " " << cell->GetMark();
            }
            std::cout << std::endl;
        }
    }

    void DisplayNeighbors()
    {
        for(int r = _size._x; r <= _size._width; r++) {
            for (int c = _size._y; c <= _size._height; c++) {
                std::string code = getCode(r, c);
                auto &cell = _cells.at(code);
                std::cout << "cell: " << cell->GetCode() << " neighbours: ";
                for(auto n : cell->GetNeighbors()){
                    std::cout << " " << n->GetCode() << ",";
                }
                std::cout << std::endl;
                std::cout << std::endl;
            }
        }
    }

private:
    Size _size;
    std::string _startCellCode;
    std::string _goalCellCode;
    Cell* _startCell;
    Cell* _goalCell;
    int _mark;
    std::shared_ptr<Strategy> _strategy;
    std::map<std::string, std::shared_ptr<Cell>> _cells;
    std::vector<Cell*> _cellsInWork;
};

#endif //LEE_GRID_HPP
