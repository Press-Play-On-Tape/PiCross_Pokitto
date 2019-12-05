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
    
    if (PC::buttons.pressed(BTN_C)) {
        this->showMenu = true;
    }
	else {


		// Normal play ..

		if (!this->gameOver && !this->showMenu) {
				
			if (PC::buttons.pressed(BTN_LEFT))	{
			
				puzzle.decX();
				if (!(PC::buttons.pressed(BTN_A)) && (PC::buttons.repeat(BTN_A, 1))) { puzzle.setGrid(this->lastUpdate); }
				if (!(PC::buttons.pressed(BTN_B)) && (PC::buttons.repeat(BTN_B, 1))) { puzzle.setGrid(this->lastUpdate); }
		
			}
		
			if (PC::buttons.pressed(BTN_RIGHT)) {
		
				puzzle.incX();
				if (!(PC::buttons.pressed(BTN_A)) && (PC::buttons.repeat(BTN_A, 1))) { puzzle.setGrid(this->lastUpdate); }
				if (!(PC::buttons.pressed(BTN_B)) && (PC::buttons.repeat(BTN_B, 1))) { puzzle.setGrid(this->lastUpdate); }
		
			}
		
			if (PC::buttons.pressed(BTN_UP))	{
		
				puzzle.decY();
				if (!(PC::buttons.pressed(BTN_A)) && (PC::buttons.repeat(BTN_A, 1))) { puzzle.setGrid(this->lastUpdate); }
				if (!(PC::buttons.pressed(BTN_B)) && (PC::buttons.repeat(BTN_B, 1))) { puzzle.setGrid(this->lastUpdate); }
		
			}
		
			if (PC::buttons.pressed(BTN_DOWN)) {
		
				puzzle.incY();
				if (!(PC::buttons.pressed(BTN_A)) && (PC::buttons.repeat(BTN_A, 1))) { puzzle.setGrid(this->lastUpdate); }
				if (!(PC::buttons.pressed(BTN_B)) && (PC::buttons.repeat(BTN_B, 1))) { puzzle.setGrid(this->lastUpdate); }
		
			}

			uint8_t xPos = this->marginLeft + (puzzle.getX() * Constants::GridWidthX);
			uint8_t yPos = this->marginTop + (puzzle.getY() * Constants::GridWidthY);


			// Handle vertical scrolling ..

			if (yPos >= 165) { 
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
						this->lastUpdate = GridValue::Blank;
						break;
						
					default: break;

				}
				
			}

			if (PC::buttons.pressed(BTN_B)) {

				GridValue current = puzzle.getGrid(FilterValue::PlayerSelection);

				switch (current) {

					case GridValue::Blank:	
					case GridValue::Selected:	
						puzzle.setGrid(GridValue::Marked);
						this->lastUpdate = GridValue::Marked;
						break;

					case GridValue::Marked:	
						puzzle.setGrid(GridValue::Blank);
						this->lastUpdate = GridValue::Blank;
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

			if (this->showMenu) {
		
				if (PC::buttons.pressed(BTN_UP) && this->menuOption > 0)	{
			
					this->menuOption--;
			
				}
			
				if (PC::buttons.pressed(BTN_DOWN) && this->menuOption < 2) {
			
					this->menuOption++;
			
				}

				if (PC::buttons.pressed(BTN_A)) {

					switch (this->menuOption)	{

						case 0:
							puzzle.saveCookie();
							this->showMenu = false;
							break;

						case 1:

							for (uint8_t x = 0; x < 16; x++) {

								for (uint8_t y = 0; y < 16; y++) {
									
									puzzle.setGrid(x, y, GridValue::Blank);

								}

							}

							puzzle.setX(0);
							puzzle.setY(0);
							puzzle.saveCookie();
							this->showMenu = false;
							break;

						case 2:
							puzzle.saveCookie();
							machine.changeState(GameStateType::SelectPuzzle);
							break;
						
					}

				}

				if (PC::buttons.pressed(BTN_B) || PC::buttons.pressed(BTN_C)) {
				
					this->showMenu = false;
				
				}

			}

		}

	}

}