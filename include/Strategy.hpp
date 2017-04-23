//
// Created by User on 22.04.2017.
//

#ifndef LEE_STRATEGY_HPP
#define LEE_STRATEGY_HPP

#include <memory>
#include <map>

NAMESPACE_BEGIN

struct Strategy {
    virtual ~Strategy(){};
    virtual void CreateRelations(const Size& border, std::map<std::string, std::shared_ptr<Cell>>& cells) = 0;
};

struct Orthogonal : public Strategy {
    ~Orthogonal(){};
    void CreateRelations(const Size& border, std::map<std::string, std::shared_ptr<Cell>>& cells) override
    {
        for(int r = border._x; r <= border._width; r++){
            for(int c = border._y; c <= border._height; c++){
                std::string code = getCode(r, c);
                auto& cell = cells.at(code);
                auto point = cell->GetPoint();
                if(point.possibleW(border)){
                    auto neighbor = cells.at(getCodeForW(point)).get();
                    cell->AddNeighbor(neighbor);
                }
                if(point.possibleN(border)){
                    auto neighbor = cells.at(getCodeForN(point)).get();
                    cell->AddNeighbor(neighbor);
                }
                if(point.possibleE(border)){
                    auto neighbor = cells.at(getCodeForE(point)).get();
                    cell->AddNeighbor(neighbor);
                }
                if(point.possibleS(border)){
                    auto neighbor = cells.at(getCodeForS(point)).get();
                    cell->AddNeighbor(neighbor);
                }
            }
        }
    }
};

struct OrthogonalDiagonal : public Strategy {
    ~OrthogonalDiagonal(){};
    void CreateRelations(const Size& border, std::map<std::string, std::shared_ptr<Cell>>& cells) override
    {
        for(int r = border._x; r <= border._width; r++){
            for(int c = border._y; c <= border._height; c++){
                std::string code = getCode(r, c);
                auto& cell = cells.at(code);
                auto point = cell->GetPoint();
                if(point.possibleW(border)){
                    auto neighbor = cells.at(getCodeForW(point)).get();
                    cell->AddNeighbor(neighbor);
                }
                if(point.possibleWN(border)){
                    auto neighbor = cells.at(getCodeForWN(point)).get();
                    cell->AddNeighbor(neighbor);
                }
                if(point.possibleN(border)){
                    auto neighbor = cells.at(getCodeForN(point)).get();
                    cell->AddNeighbor(neighbor);
                }
                if(point.possibleNE(border)){
                    auto neighbor = cells.at(getCodeForNE(point)).get();
                    cell->AddNeighbor(neighbor);
                }
                if(point.possibleE(border)){
                    auto neighbor = cells.at(getCodeForE(point)).get();
                    cell->AddNeighbor(neighbor);
                }
                if(point.possibleES(border)){
                    auto neighbor = cells.at(getCodeForES(point)).get();
                    cell->AddNeighbor(neighbor);
                }
                if(point.possibleS(border)){
                    auto neighbor = cells.at(getCodeForS(point)).get();
                    cell->AddNeighbor(neighbor);
                }
                if(point.possibleSW(border)){
                    auto neighbor = cells.at(getCodeForSW(point)).get();
                    cell->AddNeighbor(neighbor);
                }
            }
        }
    }
};

NAMESPACE_END

#endif //LEE_STRATEGY_HPP
