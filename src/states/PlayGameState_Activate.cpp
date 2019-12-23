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


    // Work out offsets ..
    
    if (this->marginLeft + (puzzle.getSize() * Constants::GridWidthX) < 220) {
        this->puzzleLeft = (220 - this->marginLeft - (puzzle.getSize() * Constants::GridWidthX) ) / 2;
    }
    else {
        this->puzzleLeft = 0;
    }
    
    if (this->marginTop + (puzzle.getSize() * Constants::GridWidthY) < 176) {
        this->puzzleTop = (176 - this->marginTop - (puzzle.getSize() * Constants::GridWidthY) ) / 2;
    }
    else {
        this->puzzleTop = 0;
    }
    
    this->counter = 0;
    this->viewState = ViewState::Normal;
    this->showHintGraphic = false;
    
    this->hintType = HintType::Col;
    this->hintIndexCol = 0;
    this->hintIndexRow = 0;

    puzzle.setX(0);
    puzzle.setY(0);
    puzzle.updateRowCols();
    
    int vol = Pokitto::Sound::getVolume();
    Pokitto::Sound::setVolume(0); // prevent an awful sound

    switch (puzzle.getPuzzleIndex() % 4) {
        
        case 0:
            Pokitto::Sound::playMusicStream("music/PiCross1.raw", 0);
            break;
        
        case 1:
            Pokitto::Sound::playMusicStream("music/PiCross2.raw", 0);
            break;
        
        case 2:
            Pokitto::Sound::playMusicStream("music/PiCross3.raw", 0);
            break;
        
        case 3:
            Pokitto::Sound::playMusicStream("music/PiCross4.raw", 0);
            break;
            
    }

    Pokitto::Sound::setVolume(vol);
    
}

