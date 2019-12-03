#pragma once

#include <stdint.h>

namespace Constants {
    
    constexpr uint8_t GridWidthX = 10;
    constexpr uint8_t GridWidthY = 10;
    constexpr uint8_t NumberOfNumbers = 8;
    
    constexpr uint16_t PuzzleStartChar1 = 150;
    constexpr uint16_t PuzzleStartChar2 = PuzzleStartChar1 + 1;
    constexpr uint16_t PuzzleIndex = PuzzleStartChar2 + 1;
    constexpr uint16_t PuzzleWidth = PuzzleIndex + 2;
    constexpr uint16_t PuzzleHeight = PuzzleWidth + 1;
    constexpr uint16_t PuzzleMaxRows = PuzzleHeight + 1;
    constexpr uint16_t PuzzleMaxCols = PuzzleMaxRows + 1;
    constexpr uint16_t PuzzleStart = PuzzleMaxCols + 1;
    constexpr uint16_t PuzzleCols = PuzzleStart + (16 * 16);
    constexpr uint16_t PuzzleRows = PuzzleCols + (16 * NumberOfNumbers);
    
    constexpr uint16_t PuzzlesSolved = PuzzleRows + (16 * NumberOfNumbers);
    
    constexpr uint16_t Select_Spacing = 41;
    constexpr uint16_t Select_Centre = 55;
    constexpr uint16_t Select_Top = 50;
    constexpr uint16_t Select_Label = Select_Top + 40;
    
    constexpr uint16_t BButtonDelay = 64;

                            //     5  6  7  8  9 10 11 12 13 14 15 16
    constexpr uint8_t Scale[] =  { 6, 5, 4, 4, 3, 3, 2, 2, 2, 2, 2, 2, };   
    constexpr uint8_t Offset[] = { 1, 1, 2, 0, 2, 1, 5, 4, 3, 2, 1, 0, };

}