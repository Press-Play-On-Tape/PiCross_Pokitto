#include "PlayGameState.h"
#include "../images/Images.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void PlayGameState::activate(StateMachine & machine) {

    auto & puzzle = machine.getContext().puzzle;
 
    
    this->maxSeriesRow = puzzle.getPuzzleMaxRows();
    this->maxSeriesCol = puzzle.getPuzzleMaxCols();

    this->marginLeft = 3 + this->maxSeriesRow * 7;
    this->marginTop = 2 + this->maxSeriesCol * 10;

    if (this->marginLeft + (puzzle.getSize() * Constants::GridWidthX) < 220) {
        this->puzzleLeft = (220 - this->marginLeft - (puzzle.getSize() * Constants::GridWidthX) ) / 2;
    }
    else {
        this->puzzleLeft = 0;
    }
    
    if (this->marginTop - (puzzle.getSize() * Constants::GridWidthY) < 176) {
        this->puzzleTop = (176 - this->marginTop - (puzzle.getSize() * Constants::GridWidthY) ) / 2;
    }
    else {
        this->puzzleTop = 0;
    }
    
    this->counter = 0;
    this->exitGame = false;
    this->gameOver = false;
    
    puzzle.setX(0);
    puzzle.setY(0);
    puzzle.updateRowCols();

}

