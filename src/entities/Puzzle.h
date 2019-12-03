#pragma once

#include "../utils/Constants.h"
#include "../utils/Enums.h"
#include "../utils/GameCookie.h"

class Puzzle { 

  public:

    Puzzle();
    
    void setCookie(GameCookie *cookie);
    GameCookie* getCookie();

    uint16_t getPuzzleIndex();
    void setPuzzleIndex(uint16_t value);

    uint8_t getX();
    uint8_t getY();
    uint8_t getSize();
    GridValue getGrid(FilterValue filterValue);
    GridValue getGrid(uint8_t x, uint8_t y, FilterValue filterValue);
    uint8_t getCol(uint8_t col, uint8_t index);
    uint8_t getRow(uint8_t col, uint8_t index);
    uint8_t getPuzzleMaxRows();
    uint8_t getPuzzleMaxCols();
    bool getPuzzlesSolved(uint16_t index);

    void setX(uint8_t value);
    void setY(uint8_t value);
    void setSize(uint8_t value);
    void setGrid(GridValue value);
    void setGrid(uint8_t x, uint8_t y, GridValue value);
    void setCol(uint8_t col, uint8_t index, uint8_t value);
    void setRow(uint8_t col, uint8_t index, uint8_t value);

    void setPuzzleMaxRow(uint8_t value);
    void setPuzzleMaxCol(uint8_t value);
    void setPuzzlesSolved(uint16_t index, bool val);

    void incX();
    void decX();
    void incY();
    void decY();

    bool isColMatch(uint8_t col);
    bool isRowMatch(uint8_t row);
    void updateRowCols();
    void saveCookie();

  private:

    GameCookie *cookie;
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t rows[Constants::NumberOfNumbers * 16];
    uint8_t cols[Constants::NumberOfNumbers * 16];

};
