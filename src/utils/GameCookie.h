#pragma once

#include "Pokitto.h"
#include "PokittoCookie.h"
#include "Enums.h"

class GameCookie : public Pokitto::Cookie {

  public:
    uint16_t puzzleIndex;
    uint8_t puzzleWidth;
    uint8_t puzzleHeight;
    uint8_t puzzleMaxRows;
    uint8_t puzzleMaxCols;
    uint8_t puzzleData[8 * 16];   // Packed
    uint8_t puzzleCols[16 * 4];    // Packed
    uint8_t puzzleRows[16 * 4];    // Packed
    uint8_t puzzlesSolved[300 / 8];

  public:

    uint8_t getPuzzleCols(uint8_t index) {

      uint8_t val = this->puzzleCols[index / 2];

      if (index % 2 == 0) {
        return val & 0x0F;        
      }
      else {
        return val >> 4;        
      }   

    }

    void setPuzzleCols(uint8_t index, uint8_t value) {

      uint8_t val = this->puzzleCols[index / 2];

      if (index % 2 == 0) {
        this->puzzleCols[index / 2] = (val & 0xF0) | value;        
      }
      else {
        this->puzzleCols[index / 2] = (val & 0x0F) | (value << 4);        
      }

    }

    uint8_t getPuzzleRows(uint8_t index) {

      uint8_t val = this->puzzleRows[index / 2];

      if (index % 2 == 0) {
        return val & 0x0F;        
      }
      else {
        return val >> 4;        
      }   

    }

    void setPuzzleRows(uint8_t index, uint8_t value) {

      uint8_t val = this->puzzleRows[index / 2];

      if (index % 2 == 0) {
        this->puzzleRows[index / 2] = (val & 0xF0) | value;        
      }
      else {
        this->puzzleRows[index / 2] = (val & 0x0F) | (value << 4);        
      }

    }

    uint8_t getPuzzlesSolved(uint8_t index) {

      uint8_t val = this->puzzlesSolved[index / 8];
      return val & (1 << (index % 8));        

    }

    void setPuzzlesSolved(uint8_t index, bool value) {

      uint8_t val = this->puzzlesSolved[index / 8];
      val = (val & ~(1 << (index % 8))) | ((value ? 1 : 0) << (index % 8));        
      this->puzzlesSolved[index / 8] = val;
      
    }

    uint8_t getPuzzleData(uint8_t pos) {

      uint8_t val = this->puzzleData[pos / 2];

      if (pos % 2 == 0) {
        return val & 0x0F;        
      }
      else {
        return val >> 4;        
      }

    }

    void setPuzzleData(uint8_t pos, GridValue gridValue) {

      uint8_t val = this->puzzleData[pos / 2];

      if (pos % 2 == 0) {
        this->puzzleData[pos / 2] = (val & 0xF0) | static_cast<uint8_t>(gridValue);        
      }
      else {
        this->puzzleData[pos / 2] = (val & 0x0F) | (static_cast<uint8_t>(gridValue) << 4);        
      }

    }

    void setPuzzleData_KeepSelectedImage(uint8_t pos, GridValue gridValue) {

      uint8_t val = this->puzzleData[pos / 2];

      if (pos % 2 == 0) {
        this->puzzleData[pos / 2] = (val & 0xF4) | static_cast<uint8_t>(gridValue);        
      }
      else {
        this->puzzleData[pos / 2] = (val & 0x4F) | (static_cast<uint8_t>(gridValue) << 4);        
      }

    }

};