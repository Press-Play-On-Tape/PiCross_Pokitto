#include "PlayGameState.h"
#include "../images/Images.h"
#include "../utils/Enums.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void PlayGameState::update(StateMachine & machine) {

    auto & puzzle = machine.getContext().puzzle;


    // Exit game?
    
    if (PC::buttons.held(BTN_B, 100)) {
        this->exitGame = true;
    }


	// Normal play ..

	if (!this->gameOver && !this->exitGame) {
    	    
    	if (PC::buttons.pressed(BTN_LEFT))	{
    	
    		puzzle.decX();
    		if (!(PC::buttons.pressed(BTN_A)) && (PC::buttons.repeat(BTN_A, 1))) { puzzle.setGrid(this->lastUpdate); }
    
    	}
    
    	if (PC::buttons.pressed(BTN_RIGHT)) {
    
    		puzzle.incX();
    		if (!(PC::buttons.pressed(BTN_A)) && (PC::buttons.repeat(BTN_A, 1))) { puzzle.setGrid(this->lastUpdate); }
    
    	}
    
    	if (PC::buttons.pressed(BTN_UP))	{
    
    		puzzle.decY();
    		if (!(PC::buttons.pressed(BTN_A)) && (PC::buttons.repeat(BTN_A, 1))) { puzzle.setGrid(this->lastUpdate); }
    
    	}
    
    	if (PC::buttons.pressed(BTN_DOWN)) {
    
    		puzzle.incY();
    		if (!(PC::buttons.pressed(BTN_A)) && (PC::buttons.repeat(BTN_A, 1))) { puzzle.setGrid(this->lastUpdate); }
    
    	}

		uint8_t xPos = this->marginLeft + (puzzle.getX() * Constants::GridWidthX);
		uint8_t yPos = this->marginTop + (puzzle.getY() * Constants::GridWidthY);

// 		if (xPos >= 119) {
// 			this->xOffset = xPos - 119;
// 		}
// 		else {
// 			this->xOffset = 0;
// 		}

		if (yPos >= 165) { //55
			this->yOffset = yPos - 165;
		}
		else {
			this->yOffset = 0;
		}

		if (PC::buttons.pressed(BTN_A)) {

			GridValue current = puzzle.getGrid(FilterValue::PlayerSelection);

			switch (current) {

				case GridValue::Blank:	
				case GridValue::Marked:	
					puzzle.setGrid(GridValue::Selected);
					this->lastUpdate = GridValue::Selected;
					break;

				case GridValue::Selected:	
					puzzle.setGrid(GridValue::Blank);
					lastUpdate = GridValue::Blank;
					break;
					
				default: break;

			}
			
		}

		if (PC::buttons.released(BTN_B)) {

			GridValue current = puzzle.getGrid(FilterValue::PlayerSelection);

			switch (current) {

				case GridValue::Blank:	
				case GridValue::Selected:	
					puzzle.setGrid(GridValue::Marked);
					break;

				case GridValue::Marked:	
					puzzle.setGrid(GridValue::Blank);
					break;
										
				default: break;
					
			}
			
		}

	}
	else {

		if (this->gameOver) {

			if (this->counter < 2) {

			 	this->counter++;
				
			}
			else {

				if (PC::buttons.pressed(BTN_A)) {

					machine.changeState(GameStateType::SelectPuzzle);

				}

			}

		}

		if (this->exitGame) {

			if (PC::buttons.pressed(BTN_A)) {

				puzzle.saveCookie();
				machine.changeState(GameStateType::SelectPuzzle);

			}

			if (PC::buttons.pressed(BTN_B)) {
			
				this->exitGame = false;
			
			}

		}

	}

}