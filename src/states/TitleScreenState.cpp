#include "TitleScreenState.h"
#include "../images/Images.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;

constexpr const static uint8_t UPLOAD_DELAY = 16;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void TitleScreenState::activate(StateMachine & machine) {

	(void)machine;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void TitleScreenState::update(StateMachine & machine) {


	// Handle other input ..

	if (PC::buttons.pressed(BTN_A)) {
		machine.changeState(GameStateType::SelectPuzzle); 
	}

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void TitleScreenState::render(StateMachine & machine) {

	(void)machine;

    PD::fillScreen(1);
    
    
    // Render top and bottom binders ..

    for (int16_t x = -25; x < 220; x = x + 26) {

        PD::drawBitmap(x, 0, Images::Binder_Top);
        PD::drawBitmap(x, 149, Images::Binder_Bottom);
    
    }


    PD::drawBitmap(11, 64, Images::PiCrossHeading);
    

}
