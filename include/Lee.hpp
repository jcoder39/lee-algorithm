//
// Created by slavik on 4/20/17.
//

#ifndef LEE_LEE_HPP
#define LEE_LEE_HPP

#define NAMESPACE_BEGIN namespace name { namespace bvv { namespace Lee {
#define NAMESPACE_END   } } }

#include <string>
#include "Settings.hpp"

NAMESPACE_BEGIN

static std::string getCode(int x, int y);

struct Size {
    int _x, _y, _width, _height;

    Size(int x, int y, int width, int height) : _x(x), _y(y), _width(width), _height(height){}
};

struct Point {
    int _x, _y;

    Point(int x, int y) : _x(x), _y(y){}

    Point operator-(const Point& another)
    {
    }

    bool possibleW(const Size& border) {
        return _x - 1 >= border._x;
    }

    bool possibleWN(const Size& border){
        int x = _x - 1;
        int y = _y - 1;
        return x >= border._x && y >= border._y;
    }

    bool possibleN(const Size& border){
        return _y - 1 >= border._y;
    }

    bool possibleNE(const Size& border){
        int x = _x + 1;
        int y = _y - 1;
        return x <= border._width && y >= border._y;
    }

    bool possibleE(const Size& border) {
        return _x + 1 <= border._width;
    }

    bool possibleES(const Size& border){
        int x = _x + 1;
        int y = _y + 1;
        return x <= border._width && y <= border._height;
    }

    bool possibleS(const Size& border){
        return _y + 1 <= border._height;
    }

    bool possibleSW(const Size& border){
        int x = _x - 1;
        int y = _y + 1;
        return x >= border._x && y <= border._height;
    }
};

struct Path {
    enum Status {
        OK,
        WRONG_PATH
    };

    Path(Status status, const std::vector<std::string>& path) : _status(status), _path(path){};

    Status _status;
    std::vector<std::string> _path;
};

std::string getCode(int x, int y)
{
    std::string temp;
    temp += std::to_string(x);
    temp += std::to_string(y);
    return temp;
}

std::string getCodeForW(const Point& point){
    return getCode(point._x - 1, point._y);
}

std::string getCodeForWN(const Point& point){
    return getCode(point._x - 1, point._y - 1);
}

std::string getCodeForN(const Point& point){
    return getCode(point._x, point._y - 1);
}

std::string getCodeForNE(const Point& point){
    return getCode(point._x + 1, point._y - 1);
}

std::string getCodeForE(const Point& point){
    return getCode(point._x + 1, point._y);
}

std::string getCodeForES(const Point& point){
    return getCode(point._x + 1, point._y + 1);
}

std::string getCodeForS(const Point& point){
    return getCode(point._x, point._y + 1);
}

std::string getCodeForSW(const Point& point){
    return getCode(point._x - 1, point._y + 1);
}

NAMESPACE_END

#include "Cell.hpp"
#include "Strategy.hpp"
#include "Grid.hpp"

#endif //LEE_LEE_HPP
