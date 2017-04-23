//
// Created by slavik on 4/19/17.
//

#ifndef LEE_CELL_HPP
#define LEE_CELL_HPP

#include <vector>
#include <string>
#include "Lee.hpp"

NAMESPACE_BEGIN

class Cell
{
public:
    Cell(Point point, int value) : _point(point), _value(value), _mark(0), _marked(false)
    {
        _code = std::to_string(_point._x) + std::to_string(_point._y);
    }

    std::string& GetCode()
    {
        return _code;
    }

    int GetValue()
    {
        return _value;
    }

    int GetMark()
    {
        return _mark;
    }

    void SetMark(int mark)
    {
        _mark = mark;
        _marked = true;
    }

    void AddNeighbor(Cell* const neighbor)
    {
        _neighbors.push_back(neighbor);
    }

    std::vector<Cell*>& GetNeighbors()
    {
        return _neighbors;
    }

    bool isMarked()
    {
        return _marked;
    }

    Point GetPoint()
    {
        return _point;
    }

    Cell* GetNeighborWithMinMark()
    {
        for(auto cell : _neighbors){
            if(cell->GetMark() < 0){
                continue;
            }
            if(cell->GetMark() < _mark){
                return cell;
            }
        }
        return nullptr;
    }

private:
    Point _point;
    int _value;
    bool _marked;
    int _mark;
    std::vector<Cell*> _neighbors;
    std::string _code;
};

NAMESPACE_END

#endif //LEE_CELL_HPP
