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


    // Flash the cursor?
    
    bool flash = true;
    this->flashCount++;  
    
    switch (this->flashCount) {
        
        case 0 ... 23:
            flash = true;
            break;
            
        case 24 ... 47:
            flash = false;
            break;
            
        case 48:
            flash = true;
            this->flashCount = 0;
            break;
        
    }


    
    // Render puzzle ..

    uint8_t size = puzzle.getSize();
    uint8_t completedRows = 0;


    PD::fillScreen(7);
    PD::setColor(5, 7);


    // Render binder left and right ..
    
    if (puzzle.getSize() < 15) {

        PD::drawBitmap(0, 0, Images::Binder_Left);

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
                    PD::setColor(5);
                    PD::fillRectangle(this->puzzleLeft + this->marginLeft + (x * Constants::GridWidthX) + 2 - this->xOffset, this->puzzleTop + this->marginTop + (y * Constants::GridWidthY) + 2 - this->yOffset, 7, 6);
                    break;
                
                case GridValue::Marked:
                    PD::setColor(6);
                    PD::fillRectangle(this->puzzleLeft + this->marginLeft + (x * Constants::GridWidthX) + 2 - this->xOffset, this->puzzleTop + this->marginTop + (y * Constants::GridWidthY) + 2 - this->yOffset, 7, 6);
                    break;
            
            }
        
        }
    
    }
    
    
    // Render column headers ..
    
    for (uint8_t x = 0; x < size; x++) {

        if (puzzle.isColMatch(x)) {
        
            PD::setColor(5);
            PD::fillRect(this->puzzleLeft + this->marginLeft + (x * Constants::GridWidthX) + 1 - this->xOffset, this->puzzleTop - this->yOffset, 9, this->marginTop - 2);
            PD::setColor(7, 5);
            
            completedRows++;
        
        }
        else {
        
            PD::setColor(5, 7);
    
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
            
            PD::setColor(5);
            PD::fillRect(this->puzzleLeft + this->xOffset, this->puzzleTop + this->marginTop + (y * Constants::GridWidthY) + 1 - this->yOffset, this->marginLeft - 1, 8);
            PD::setColor(7, 5);
            
            completedRows++;
            
        }
        else {
        
            PD::setColor(5, 7);
        
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
    
    if (completedRows == 2 * size && this->viewState != ViewState::GameOver) {
        
        this->viewState = ViewState::GameOver;
        
        // Increase hint counter if the puzzle hasn't been solved before ..
        
        if (!puzzle.getPuzzlesSolved(puzzle.getPuzzleIndex())) {
        
            this->showHintGraphic = puzzle.incHintCounter();

        }
        
        puzzle.setPuzzlesSolved(puzzle.getPuzzleIndex(), true);

    }


    switch (this->viewState) {
        
        case ViewState::GameOver:
            
            switch (this->counter) {
    
              case 1:
                puzzle.saveCookie();
                break;
    
              case 2:
    
                uint8_t width = puzzle.getSize();
                uint8_t height = puzzle.getSize();
    
                uint8_t scale = Constants::Scale[puzzle.getPuzzleIndex() / 25];
                uint8_t offset = Constants::Offset[puzzle.getPuzzleIndex() / 25];
                
                PD::drawBitmap(18, 60, Images::Congratulations);
                renderPuzzleImage(176, 68, Puzzles::puzzles[puzzle.getPuzzleIndex()], scale, puzzle.getPuzzleIndex() % Constants::RenderPuzzle_NoOfColours);
                
                if (this->showHintGraphic) PD::drawBitmap(42, 110, Images::Hint);
                
                break;
    
            }
           
            break;
            
        case ViewState::Menu:

            PD::drawBitmap(107, 75, Images::Binder_Folded);
            if (puzzle.getHintCount() > 0) PD::drawBitmap(159, 147, Images::Give_Hint);
            PD::drawBitmap(214, 147 + (this->menuOption * 9), Images::ArrowLeft);
            
            break;
            
        case ViewState::Normal:

            if (flash) {
                PD::setColor(9, 8);            
                PD::drawBitmap(this->puzzleLeft + this->marginLeft + (puzzle.getX() * Constants::GridWidthX) - this->xOffset + 1, this->puzzleTop + this->marginTop + (puzzle.getY() * Constants::GridWidthY) - this->yOffset + 1, Images::Cursor);
                PD::drawRect(this->puzzleLeft + this->marginLeft + (puzzle.getX() * Constants::GridWidthX) - this->xOffset, this->puzzleTop + this->marginTop + (puzzle.getY() * Constants::GridWidthY) - this->yOffset, 10, 10);
            }
            
            break;
            
        case ViewState::Hint:
        
            if (flash) {
                
                PD::setColor(10);
                
                if (this->hintType == HintType::Col) {
                    PD::drawRect(this->puzzleLeft + this->marginLeft + (this->hintIndexCol * Constants::GridWidthX) - this->xOffset, this->puzzleTop + this->marginTop - this->yOffset, Constants::GridWidthX, (size * Constants::GridWidthY));
                }
                else {
                    PD::drawRect(this->puzzleLeft + this->marginLeft - this->xOffset, this->puzzleTop + this->marginTop + (this->hintIndexRow * Constants::GridWidthY) - this->yOffset, (size * Constants::GridWidthY), Constants::GridWidthY);  
                    
                }
            
                
            }
            
            break;
    
    }

}

