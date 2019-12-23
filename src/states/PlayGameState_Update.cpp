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

    
    switch (this->viewState) {
        
        case ViewState::Normal:
        
            if (PC::buttons.pressed(BTN_C)) {
                
                this->viewState = ViewState::Menu;
                
                if (puzzle.getHintCount() > 0) {
                    
                    this->menuOption = 0;
                    
                }
                else {
                    
                    this->menuOption = 1;
                    
                }
        
            }
        	else {
        	    
            	if (PC::buttons.pressed(BTN_LEFT))	{
    			
    				puzzle.decX();
    				this->flashCount = 0; 
    				if (!(PC::buttons.pressed(BTN_A)) && (PC::buttons.repeat(BTN_A, 1))) { puzzle.setGrid(this->lastUpdate); }
    				if (!(PC::buttons.pressed(BTN_B)) && (PC::buttons.repeat(BTN_B, 1))) { puzzle.setGrid(this->lastUpdate); }
    		
    			}
    		
    			if (PC::buttons.pressed(BTN_RIGHT)) {
    		
    				puzzle.incX();
    				this->flashCount = 0; 
    				if (!(PC::buttons.pressed(BTN_A)) && (PC::buttons.repeat(BTN_A, 1))) { puzzle.setGrid(this->lastUpdate); }
    				if (!(PC::buttons.pressed(BTN_B)) && (PC::buttons.repeat(BTN_B, 1))) { puzzle.setGrid(this->lastUpdate); }
    		
    			}
    		
    			if (PC::buttons.pressed(BTN_UP))	{
    		
    				puzzle.decY();
    				this->flashCount = 0; 
    				if (!(PC::buttons.pressed(BTN_A)) && (PC::buttons.repeat(BTN_A, 1))) { puzzle.setGrid(this->lastUpdate); }
    				if (!(PC::buttons.pressed(BTN_B)) && (PC::buttons.repeat(BTN_B, 1))) { puzzle.setGrid(this->lastUpdate); }
    		
    			}
    		
    			if (PC::buttons.pressed(BTN_DOWN)) {
    		
    				puzzle.incY();
    				this->flashCount = 0; 
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
        	
        	break;
        	
        case ViewState::GameOver:

			if (this->counter < 2) {

				this->counter++;
				
			}
			else {

				if (PC::buttons.pressed(BTN_A)) {

					machine.changeState(GameStateType::SelectPuzzle);

				}

			}
				
			break;
        
        case ViewState::Menu:
        
    		if (puzzle.getHintCount() > 0) {

				if (PC::buttons.pressed(BTN_UP) && this->menuOption > 0)	{
			
					this->menuOption--;
			
				}
				
	        }
	        else {

				if (PC::buttons.pressed(BTN_UP) && this->menuOption > 1)	{
			
					this->menuOption--;
			
				}

	        }
		
			if (PC::buttons.pressed(BTN_DOWN) && this->menuOption < 2) {
		
				this->menuOption++;
		
			}

			if (PC::buttons.pressed(BTN_A)) {

				switch (this->menuOption)	{

					case 0:
						this->viewState = ViewState::Hint;
						this->hintIndexRow = puzzle.getY();
						this->hintIndexCol = puzzle.getX();
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
						this->viewState = ViewState::Normal;
						break;

					case 2:
						puzzle.saveCookie();
						machine.changeState(GameStateType::SelectPuzzle);
						break;
					
				}

			}

			if (PC::buttons.pressed(BTN_B) || PC::buttons.pressed(BTN_C)) {
			
				this->viewState = ViewState::Normal;
			
			}

			break;
			
		case ViewState::Hint:
	
        	if (PC::buttons.pressed(BTN_LEFT))	{
			
    			this->flashCount = 0; 
    			
			    if (this->hintIndexCol > 0 && this->hintType == HintType::Col) {
			        this->hintIndexCol--;
			    }
			    else {
    			    if (this->hintType == HintType::Row) {
    			        this->hintType = HintType::Col;
    			    }
			    }

			}
		
			if (PC::buttons.pressed(BTN_RIGHT)) {
			
    			this->flashCount = 0; 
			
			    if (this->hintIndexCol < puzzle.getSize() - 1 && this->hintType == HintType::Col) {
			        this->hintIndexCol++;
			    }
			    else {
    			    if (this->hintType == HintType::Row) {
    			        this->hintType = HintType::Col;
    			    }
			    }

			}
		
			if (PC::buttons.pressed(BTN_UP)) {
			
    			this->flashCount = 0; 
			
			    if (this->hintIndexRow > 0 && this->hintType == HintType::Row) {
			        this->hintIndexRow--;
			    }
			    else {
    			    if (this->hintType == HintType::Col) {
    			        this->hintType = HintType::Row;
    			    }
			    }
		
			}
		
			if (PC::buttons.pressed(BTN_DOWN)) {
			
    			this->flashCount = 0; 
			
			    if (this->hintIndexRow < puzzle.getSize() - 1 && this->hintType == HintType::Row) {
			        this->hintIndexRow++;
			    }
			    else {
    			    if (this->hintType == HintType::Col) {
    			        this->hintType = HintType::Row;
    			    }
			    }
		
			}

			if (PC::buttons.pressed(BTN_B)) {
           	
           	    this->viewState = ViewState::Normal;
           	    puzzle.setX(this->hintIndexCol);
           	    puzzle.setY(this->hintIndexRow);
           		
			}

			if (PC::buttons.pressed(BTN_A)) {
			
			    if (this->hintType == HintType::Col) {
			        
			        for (uint8_t y = 0; y < puzzle.getSize(); y++) {
			            
			            GridValue value = puzzle.getGrid(this->hintIndexCol, y, FilterValue::SelectedInImage);
			            puzzle.setGrid(this->hintIndexCol, y, value != GridValue::Blank ? GridValue::Selected : GridValue::Marked);
			            
			        }
			        
			    }
			    else {
			        
			        for (uint8_t x = 0; x < puzzle.getSize(); x++) {
			            
			            GridValue value = puzzle.getGrid(x, this->hintIndexRow, FilterValue::SelectedInImage);
			            puzzle.setGrid(x, this->hintIndexRow, value != GridValue::Blank ? GridValue::Selected : GridValue::Marked);
			            
			        }
			        
			    }

           	    this->viewState = ViewState::Normal;
           	    puzzle.decHintCount();
           		
			}
		

			// Handle vertical scrolling ..
		    
	    	uint8_t xPos = this->marginLeft + (this->hintIndexCol * Constants::GridWidthX);
			uint8_t yPos = this->marginTop + (this->hintIndexRow * Constants::GridWidthY);

			if (yPos >= 165) { 
				this->yOffset = yPos - 165;
			}
			else {
				this->yOffset = 0;
			}
			
			
		    break;
        
    }


}