#include "PlayGameState.h"
#include "../puzzles/Puzzles.h"
#include "../images/Images.h"
#include "../utils/Utils.h"
#include "../utils/Enums.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ---------------------------------------------------------------------------------------------------------------------------
//  Render the state .. 
// ---------------------------------------------------------------------------------------------------------------------------
// 
void PlayGameState::render(StateMachine & machine) {

    uint8_t const solidLines[] = {
        0, 0, 0, 0, 0,    // 0
        0, 0, 0, 0, 0,    // 1
        0, 2, 0, 0, 0,    // 2
        0, 3, 0, 0, 0,    // 3
        0, 4, 0, 0, 0,    // 4
        0, 5, 0, 0, 0,    // 5
        0, 3, 6, 0, 0,    // 6
        0, 7, 0, 0, 0,    // 7
        0, 4, 8, 0, 0,    // 8
        0, 3, 6, 9, 0,    // 9
        0, 5, 10, 0, 0,   // 10
        0, 11, 0, 0, 0,   // 11
        0, 4, 8, 12, 0,   // 12
        0, 13, 0, 0, 0,   // 13
        0, 7, 14, 0, 0,   // 14
        0, 5, 10, 15, 0,  // 15
        0, 4, 8, 12, 16,  // 16
    };

    auto & puzzle = machine.getContext().puzzle;

    bool flash = getFrameCountHalf(48);  
    uint8_t size = puzzle.getSize();
    uint8_t completedRows = 0;


    PD::fillScreen(1);
    PD::setColor(8);


    // Render biner left and right ..
    
    if (puzzle.getSize() < 15) {

        PD::drawBitmap(0, 0, Images::Binder_Left);
        PD::drawBitmap(208, 0, Images::Binder_Right);

    }    

    for (uint8_t x = 0; x <= size; x++) {
    
        
        // Horizontal and Vertical lines ..
        
        for (uint8_t z = size * 5; z < (size * 5) + 5; z++) {
            
            if (x == solidLines[z]) {

                PD::drawColumn(this->puzzleLeft + this->marginLeft + (x * Constants::GridWidthX) - this->xOffset, this->puzzleTop + this->marginTop - this->yOffset, this->puzzleTop + this->marginTop - this->yOffset + (size * Constants::GridWidthY)); 
                PD::drawRow(this->puzzleLeft + this->marginLeft - this->xOffset, this->puzzleLeft + this->marginLeft - this->xOffset + (size * Constants::GridWidthX), this->puzzleTop + this->marginTop + (x * Constants::GridWidthY) - this->yOffset);  

            }
        
        }
        
        drawDottedColumn(this->puzzleLeft + this->marginLeft + (x * Constants::GridWidthX) - this->xOffset, this->puzzleTop, this->puzzleTop + this->marginTop - this->yOffset + (size * Constants::GridWidthY)); 
        drawDottedRow(this->puzzleLeft, this->puzzleLeft + this->marginLeft + (size * Constants::GridWidthX) - this->xOffset, this->puzzleTop + this->marginTop + (x * Constants::GridWidthY) - this->yOffset);  
    
    }

    for (uint8_t x = 0; x < size; x++) {
        
        for (uint8_t y = 0; y < size; y++) {
            
            GridValue gridValue = puzzle.getGrid(x, y, FilterValue::PlayerSelection);
            
            switch (gridValue) {
                
                case GridValue::Blank:
                    break;
                
                case GridValue::Selected:
                    PD::setColor(8);
                    PD::fillRectangle(this->puzzleLeft + this->marginLeft + (x * Constants::GridWidthX) + 2 - this->xOffset, this->puzzleTop + this->marginTop + (y * Constants::GridWidthY) + 2 - this->yOffset, 7, 6);
                    break;
                
                case GridValue::Marked:
                    PD::setColor(4);
                    PD::fillRectangle(this->puzzleLeft + this->marginLeft + (x * Constants::GridWidthX) + 2 - this->xOffset, this->puzzleTop + this->marginTop + (y * Constants::GridWidthY) + 2 - this->yOffset, 7, 6);
//                    PD::drawBitmap(this->marginLeft + (x * Constants::GridWidthX) + 2 - this->xOffset, this->marginTop + (y * Constants::GridWidthY) + 2 - this->yOffset, Images::Marked);
                    break;
            
            }
        
        }
    
    }
    
    
    // Render column headers ..
    
    for (uint8_t x = 0; x < size; x++) {

        if (puzzle.isColMatch(x)) {
        
            PD::setColor(8);
            PD::fillRect(this->puzzleLeft + this->marginLeft + (x * Constants::GridWidthX) + 1 - this->xOffset, this->puzzleTop - this->yOffset, 9, this->marginTop - 2);
            PD::setColor(1, 8);
            
            completedRows++;
        
        }
        else {
        
            PD::setColor(8, 1);
    
        }
    
        for (uint8_t y = 0; y < Constants::NumberOfNumbers; y++) {
        
            uint8_t val = puzzle.getCol(x, y);
            
            if (val != 0) {
                
                PD::setCursor(this->puzzleLeft + this->marginLeft + (x * Constants::GridWidthX) + 3 - (val >= 10 ? 3 : 0) - this->xOffset, this->puzzleTop + 1 - this->yOffset + (y * 10));
                PD::print(static_cast<int8_t>(val));

            }
            
        }
    
    }

    
    // Render row headers ..
    
    for (uint8_t y = 0; y < size; y++) {

        if (puzzle.isRowMatch(y)) {
            
            PD::setColor(8);
            PD::fillRect(this->puzzleLeft + this->xOffset, this->puzzleTop + this->marginTop + (y * Constants::GridWidthY) + 1 - this->yOffset, this->marginLeft - 1, 8);
            PD::setColor(1, 8);
            
            completedRows++;
            
        }
        else {
        
            PD::setColor(8, 1);
        
        }
        
        uint8_t largerThan10 = 0;
        
        for (uint8_t x = 0; x < Constants::NumberOfNumbers; x++) {
            
            uint8_t val = puzzle.getRow(y, x);
            
            if (val != 0) {
            
                if (val >= 10) largerThan10++;

                PD::setCursor(this->puzzleLeft + 1 + (x * 7) - this->xOffset, this->puzzleTop + this->marginTop + (y * Constants::GridWidthY) + 2 - this->yOffset);
                PD::print(static_cast<int8_t>(val));

            }
        
        }
    
    }

    PD::setColor(1);


    // Game over?
    
    if (completedRows == 2 * size && !this->gameOver) {
        
        this->gameOver = true;
        puzzle.setPuzzlesSolved(puzzle.getPuzzleIndex(), true);

    }

    if (this->gameOver) {

        switch (this->counter) {

          case 1:
            puzzle.saveCookie();
            break;

          case 2:

            uint8_t width = puzzle.getSize();
            uint8_t height = puzzle.getSize();

            uint8_t scale = Constants::Scale[puzzle.getPuzzleIndex() / 25];
            uint8_t offset = Constants::Offset[puzzle.getPuzzleIndex() / 25];
            
            PD::drawBitmap(6, 20, Images::Congratulations);
            
            renderPuzzleImage(166, 30, Puzzles::puzzles[puzzle.getPuzzleIndex()], scale);

            
            // PD::drawBitmap(101 - (width / 2), 32 - (height / 2), Images::Puzzles[puzzle.getPuzzleIndex()]);
            break;

       }
    
    }
    else if (this->showMenu) {
    
        PD::drawBitmap(55, 8, Images::Binder_Folded);

        PD::setColor(1, 11);
        PD::setCursor(158, 145);
        PD::print("Save Game");
        PD::setCursor(153, 155);
        PD::print("Reset Game");
        PD::setCursor(159, 165);
        PD::print("Exit Game");

        PD::drawBitmap(214, 145 + (this->menuOption * 10), Images::ArrowLeft);

    }
    else {
    
        if (flash) {
            PD::setColor(8, 1);            
            PD::drawBitmap(this->puzzleLeft + this->marginLeft + (puzzle.getX() * Constants::GridWidthX) - this->xOffset + 1, this->puzzleTop + this->marginTop + (puzzle.getY() * Constants::GridWidthY) - this->yOffset + 1, Images::Cursor);
            PD::drawRect(this->puzzleLeft + this->marginLeft + (puzzle.getX() * Constants::GridWidthX) - this->xOffset, this->puzzleTop + this->marginTop + (puzzle.getY() * Constants::GridWidthY) - this->yOffset, 10, 10);
        }
    
    }

}

