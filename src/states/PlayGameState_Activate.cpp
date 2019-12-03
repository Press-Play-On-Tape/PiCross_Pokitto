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
    
    this->counter = 0;
    this->exitGame = false;
    this->gameOver = false;
    
    puzzle.setX(0);
    puzzle.setY(0);
    puzzle.updateRowCols();

}

