#include "SelectPuzzleState.h"

#include "Pokitto.h"

#include "../utils/Constants.h"
#include "../utils/Utils.h"
#include "../images/Images.h"
#include "../entities/Puzzle.h"
#include "../puzzles/Puzzles.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void SelectPuzzleState::activate(StateMachine & machine) {

    auto & puzzle = machine.getContext().puzzle;

    uint16_t numberOfImages = ArrayLength(Puzzles::puzzles);
    this->puzzleIndex = puzzle.getPuzzleIndex();

    
    // If the current puzzle is equal to 0 and there are no dimensions, it is probably time to flash the memory with a puzzle ..
    
    if (puzzle.getSize() == 0) {

        this->populatePuzzle(machine, 0);
    
    }
    
    
    // If the current puzzle has been completed, then look for the next unfinished puzzle ..
    
    if (puzzle.getPuzzlesSolved(this->puzzleIndex)) {

        for (uint16_t x = this->puzzleIndex + 1; x < numberOfImages; x++) {
         
            if (!puzzle.getPuzzlesSolved(x)) {
                
                this->puzzleIndex = x;
                break;
            
            }
        
        }
    
    }

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void SelectPuzzleState::update(StateMachine & machine) { 
    
    auto & puzzle = machine.getContext().puzzle;

    uint8_t puzzleIndexMod25 = this->puzzleIndex % 25;
    uint8_t puzzleRange = this->puzzleIndex / 25;


    // Navigation .. 
    
    if (PC::buttons.pressed(BTN_LEFT) && puzzleIndexMod25 > 0) {
    
        this->puzzleIndex--;
    
    }
    
    if (PC::buttons.pressed(BTN_RIGHT) && puzzleIndexMod25 < 24) {
    
        this->puzzleIndex++;
    
    }
    
    if (PC::buttons.pressed(BTN_UP) && puzzleRange > 0) {
    
        this->puzzleIndex = this->puzzleIndex - 25;
    
    }
    
    if (PC::buttons.pressed(BTN_DOWN) && puzzleRange < 11) {
    
        this->puzzleIndex = this->puzzleIndex + 25;
    
    }



    // Populate puzzle ..

    if (PC::buttons.pressed(BTN_A)) {
      
        if (puzzle.getPuzzleIndex() != this->puzzleIndex) {
            this->populatePuzzle(machine, this->puzzleIndex);
        }
        else {
        
            if (puzzle.getPuzzlesSolved(this->puzzleIndex)) {
                puzzle.setPuzzlesSolved(this->puzzleIndex, false);
                this->populatePuzzle(machine, this->puzzleIndex);
            }    
        }

        machine.changeState(GameStateType::PlayGame); 

    }

}


// ----------------------------------------------------------------------------
//  Populate a puzzle .. 
//
void SelectPuzzleState::populatePuzzle(StateMachine & machine, uint16_t puzzleIndex) {

    auto & puzzle = machine.getContext().puzzle;

    uint16_t idx = 0;
    uint8_t maxSeriesRow = 0;
    uint8_t maxSeriesCol = 0;

    const uint8_t *puzzleImg = Puzzles::puzzles[puzzleIndex];

    uint8_t width = puzzleImg[idx++];
    uint8_t height = puzzleImg[idx++];
    uint8_t height8 = (height % 8 == 0 ? height / 8 : (height / 8) + 1);
    
    puzzle.setPuzzleIndex(puzzleIndex);
    puzzle.setSize(width);

    for (uint8_t y = 0; y < height8; y++){

        for (uint8_t x = 0; x < width; x++){

            uint8_t data = puzzleImg[idx++];

            for (uint8_t z = 0; z < 8; z++) {

                GridValue val = (data & (1 << z)) > 0 ? GridValue::SelectedInImage : GridValue::Blank;
                puzzle.setGrid(x, static_cast<uint8_t>((y * 8) + z), val);

            }

        }

    }



    // Rows ..

    for (uint8_t y = 0; y < height; y++){

        uint8_t series[Constants::NumberOfNumbers];
        memset(series, 0, Constants::NumberOfNumbers);
        int8_t seriesIdx = -1;

        GridValue lastData = GridValue::Blank;
        
        for (uint8_t x = 0; x < width; x++){
            
            GridValue data = puzzle.getGrid(x, y, FilterValue::SelectedInImage);
            
            if (lastData != data) {
            
                if (data == GridValue::SelectedInImage) {
                    seriesIdx++;
                    if (seriesIdx == Constants::NumberOfNumbers) break;
                }

                lastData = data;
                
            }
            
            if (data == GridValue::SelectedInImage) {

                series[seriesIdx]++;

            }
        
        }
        
        
        for (uint8_t z = 0; z < Constants::NumberOfNumbers; z++) {
        
            if (series[z] > 0 && maxSeriesRow < z + 1) maxSeriesRow = z + 1;
            puzzle.setRow(y, z, series[z]);

        }

    }


    // Column Headers ..
    
    for (uint8_t x = 0; x < width; x++){
    
        uint8_t series[Constants::NumberOfNumbers];
        memset(series, 0, Constants::NumberOfNumbers);
        int8_t seriesIdx = -1;
        
        GridValue lastData = GridValue::Blank;
        
        for (uint8_t y = 0; y < height; y++){
        
            GridValue data = puzzle.getGrid(x, y, FilterValue::SelectedInImage);

            if (lastData != data) {
            
                if (data == GridValue::SelectedInImage) {
                    
                    seriesIdx++;
                    if (seriesIdx == Constants::NumberOfNumbers) break;

                }

                lastData = data;
                
            }
            
            if (data == GridValue::SelectedInImage) {
                series[seriesIdx]++;
            }
        
        }
        
        for (uint8_t z = 0; z < Constants::NumberOfNumbers; z++){
        
            if (series[z] > 0 && maxSeriesCol < z + 1) maxSeriesCol = z + 1;
            puzzle.setCol(x, z, series[z]);

        }

    }

    puzzle.setPuzzleMaxRow(maxSeriesRow);
    puzzle.setPuzzleMaxCol(maxSeriesCol);
    puzzle.saveCookie();

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void SelectPuzzleState::render(StateMachine & machine) {

    auto & puzzle = machine.getContext().puzzle;
    
    uint16_t puzzleRange = this->puzzleIndex / 25;
    uint8_t puzzleIndexMod25 = this->puzzleIndex % 25;
    uint8_t completed = 0;
    
    int8_t lowerLimit = (puzzleIndexMod25 - 2 < 0 ? 0 : (puzzleIndexMod25 >= 22 ? 20 : puzzleIndexMod25 - 2));
    int8_t upperLimit = (lowerLimit + 5 <= 25 ? lowerLimit + 5 : 25);
    int8_t cursorPosition = (puzzleIndexMod25 < 2 ? lowerLimit + puzzleIndexMod25 : (puzzleIndexMod25 > 22 ? lowerLimit + puzzleIndexMod25 - 20 : lowerLimit + 2));
    
    
    PD::fillScreen(1);
    
    
    // Render top and bottom binders ..

    for (int16_t x = -25; x < 220; x = x + 26) {

        PD::drawBitmap(x, 0, Images::Binder_Top);
        PD::drawBitmap(x, 149, Images::Binder_Bottom);
    
    }
    
    
    // How many of the current range have been completed?
    
    for (uint8_t x = 0; x < 25; x++) {
    
        if (puzzle.getPuzzlesSolved((puzzleRange * 25) + x)) {  
            
            completed++;
            
        }

    }

    completed = completed * 4;
    
    
    PD::drawBitmap(9, 31, Images::Selector_Top);

    for (int8_t x = lowerLimit; x < upperLimit; x++) {
        
        uint8_t xPos = x - lowerLimit;
        uint8_t width = puzzleRange + 5;
        uint8_t height = puzzleRange + 5;
        
        // if ((flash && (x == cursorPosition)) || (x != cursorPosition)) {
        PD::drawBitmap(9 + (xPos * Constants::Select_Spacing), Constants::Select_Top, Images::Box);
        // }
        
        if (puzzle.getPuzzlesSolved((puzzleRange * 25) + x)) {
            
            uint8_t scale = Constants::Scale[puzzleRange];
            uint8_t offset = Constants::Offset[puzzleRange];
        
            PD::setColor(11, 1);            
            renderPuzzleImage(9 + (xPos * Constants::Select_Spacing) + 2 + offset, Constants::Select_Top + 2 + offset, Puzzles::puzzles[(puzzleRange * 25) + x], scale);

        }
        else {
            PD::drawBitmap(10 + (xPos * Constants::Select_Spacing), Constants::Select_Top + 1, Images::QuestionMark);
        }

        
        if (x == cursorPosition) {
            PD::drawBitmap(32 + (xPos * Constants::Select_Spacing), Constants::Select_Top + 23, Images::Pen);
        }

        PD::setColor(8, 1);
        PD::setCursor(13 + (xPos * Constants::Select_Spacing) + 7, Constants::Select_Label);
        if (x + 1 < 10) PD::print("0");
        PD::print(x + 1);

    }

//     PD::setCursor(0, 120);

// for (uint8_t x = 0; x < 16; x++) {
//     PD::setColor(x);
//     PD::print((int8_t)x);
// }
    PD::setColor(9, 1);
    PD::setCursor(11, 34);
    PD::print(puzzleRange + 5);
    PD::print("x");
    PD::print(puzzleRange + 5);

    PD::setColor(1, 8);
    PD::setCursor(180, 36);
    if (completed < 100) PD::print("0");
    if (completed < 10)  PD::print("0");
    PD::print(static_cast<uint16_t>(completed));
    PD::print("%");

    if (puzzleRange > 0) PD::drawBitmap(45, 36, Images::ArrowUp);
    if (puzzleRange < 11) PD::drawBitmap(53, 36, Images::ArrowDown);

}
