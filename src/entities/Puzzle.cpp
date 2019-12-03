#include "Puzzle.h"

#include "../utils/Constants.h"
#include "../utils/Utils.h"
#include "../utils/Enums.h"
#include "../images/Images.h"

Puzzle::Puzzle() { }

void Puzzle::setCookie(GameCookie *cookie) {
    
    this->cookie = cookie;
    
}

GameCookie* Puzzle::getCookie() {
    
    return this->cookie;
    
}

uint8_t Puzzle::getX() {

  return this->x;

}

uint8_t Puzzle::getY() {

  return this->y;

}

uint8_t Puzzle::getSize() {

    return this->cookie->puzzleWidth;

}

uint16_t Puzzle::getPuzzleIndex() {

    return this->cookie->puzzleIndex;

}

GridValue Puzzle::getGrid(FilterValue filterValue) {

    uint8_t width = this->cookie->puzzleWidth;
    uint8_t val = this->cookie->getPuzzleData((this->y * width) + (this->x)) & static_cast<uint8_t>(filterValue);

    return static_cast<GridValue>(val);

}

GridValue Puzzle::getGrid(uint8_t x, uint8_t y, FilterValue filterValue) {

    uint8_t width = this->cookie->puzzleWidth;
    uint8_t val = this->cookie->getPuzzleData((y * width) + x) & static_cast<uint8_t>(filterValue);

    return static_cast<GridValue>(val);

}


uint8_t Puzzle::getCol(uint8_t col, uint8_t index) {

    return this->cookie->getPuzzleCols((col * Constants::NumberOfNumbers) + index);

}

uint8_t Puzzle::getRow(uint8_t row, uint8_t index) {

    return this->cookie->getPuzzleRows((row * Constants::NumberOfNumbers) + index);

}

void Puzzle::setX(uint8_t value) {

  this->x = value;
  
}

void Puzzle::setY(uint8_t value) {
  
  this->y = value;
  
}

void Puzzle::setSize(uint8_t value) {
  
  this->cookie->puzzleWidth = value;
  this->cookie->puzzleHeight = value;

}

void Puzzle::setPuzzleIndex(uint16_t value) {
  
  this->cookie->puzzleIndex = value;

}

void Puzzle::setGrid(GridValue value) {

    uint8_t width = this->cookie->puzzleWidth;
    this->cookie->setPuzzleData_KeepSelectedImage((this->y * width) + x, value);
    this->updateRowCols();
//    this->cookie->saveCookie();

}

void Puzzle::setGrid(uint8_t x, uint8_t y, GridValue value) {

    uint8_t width = this->cookie->puzzleWidth;
    this->cookie->setPuzzleData((y * width) + x, value);
    this->updateRowCols();

}

void Puzzle::setCol(uint8_t col, uint8_t index, uint8_t value) {

    this->cookie->setPuzzleCols((col * Constants::NumberOfNumbers) + index, value);

}

void Puzzle::setRow(uint8_t row, uint8_t index, uint8_t value) {

    this->cookie->setPuzzleRows((row * Constants::NumberOfNumbers) + index, value);

}

void Puzzle::setPuzzleMaxRow(uint8_t value) {

    this->cookie->puzzleMaxRows = value;  

}

void Puzzle::setPuzzleMaxCol(uint8_t value) {

    this->cookie->puzzleMaxCols = value;  
    
}

bool Puzzle::getPuzzlesSolved(uint16_t index) {

    return (this->cookie->getPuzzlesSolved(index));

}

void Puzzle::setPuzzlesSolved(uint16_t index, bool val) {

    this->cookie->setPuzzlesSolved(index, val);

}

void Puzzle::incX() {

    uint8_t width = this->cookie->puzzleWidth;  
    this->x++;
    if (this->x == width) this->x = 0;
  
}

void Puzzle::decX() {
    
    uint8_t width = this->cookie->puzzleWidth;    
    if (this->x == 0) this->x = width;
    this->x--;
  
}

void Puzzle::incY() {

    uint8_t height = this->cookie->puzzleHeight;  
    this->y++;
    if (this->y == height) this->y = 0;
  
}

void Puzzle::decY() {

    uint8_t height = this->cookie->puzzleHeight;  
    if (this->y == 0) this->y = height;
    this->y--;
  
}

bool Puzzle::isColMatch(uint8_t col) {

    for (uint8_t z = 0; z < Constants::NumberOfNumbers; z++) {

        if (this->cookie->getPuzzleCols((col * Constants::NumberOfNumbers) + z) != this->cols[(col * Constants::NumberOfNumbers) + z]) {
            return false;
        }

    }

    return true;

}

bool Puzzle::isRowMatch(uint8_t row) {

    for (uint8_t z = 0; z < Constants::NumberOfNumbers; z++) {

        if (this->cookie->getPuzzleRows((row * Constants::NumberOfNumbers) + z) != this->rows[(row * Constants::NumberOfNumbers) + z]) {
            return false;
        }

    }

    return true;

}
 
void Puzzle::updateRowCols() {
    
    uint8_t width = this->cookie->puzzleWidth;    
    uint8_t height = this->cookie->puzzleHeight;  
    
    
    // Rows ..

    for (uint8_t y = 0; y < height; y++){
    
        uint8_t series[Constants::NumberOfNumbers];
        memset(series, 0, Constants::NumberOfNumbers);
        int8_t seriesIdx = -1;
        
        GridValue lastData = GridValue::Blank;
        
        for (uint8_t x = 0; x < width; x++){
            
            GridValue data = this->getGrid(x, y, FilterValue::PlayerSelection);
            
            if (lastData != data) {
            
                if (data == GridValue::Selected) {
                    seriesIdx++;
                    if (seriesIdx == Constants::NumberOfNumbers) break;
                }

                lastData = data;
                
            }
            
            if (data == GridValue::Selected) {
                series[seriesIdx]++;
            }
        
        }
        
        for (uint8_t z = 0; z < Constants::NumberOfNumbers; z++){
        
            this->rows[(y * Constants::NumberOfNumbers) + z] = series[z];
        }

    }


    // Column Headers ..
  
    for (uint8_t x = 0; x < width; x++){
        
        uint8_t series[Constants::NumberOfNumbers];
        memset(series, 0, Constants::NumberOfNumbers);
        int8_t seriesIdx = -1;
        
        GridValue lastData = GridValue::Blank;
        
        for (uint8_t y = 0; y < height; y++){
        
            GridValue data = this->getGrid(x, y, FilterValue::PlayerSelection);
            
            if (lastData != data) {
            
                if (data == GridValue::Selected) {
                    seriesIdx++;
                    if (seriesIdx == Constants::NumberOfNumbers) break;
                }
                
                lastData = data;
                
            }
            if (data == GridValue::Selected) {
                series[seriesIdx]++;
            }
        
        }
        
        for (uint8_t z = 0; z < Constants::NumberOfNumbers; z++){
        
            this->cols[(x * Constants::NumberOfNumbers) + z] = series[z];

        }

    }

}

void Puzzle::saveCookie() {
 
    this->cookie->saveCookie(); 
    
}

uint8_t Puzzle::getPuzzleMaxRows() {

    return this->cookie->puzzleMaxRows;

}

uint8_t Puzzle::getPuzzleMaxCols() {
    
    return this->cookie->puzzleMaxCols;

}
