#include "SplashScreenState.h"
#include "../images/Images.h"
#include "../utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void SplashScreenState::activate(StateMachine & machine) {

  (void)machine;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void SplashScreenState::update(StateMachine & machine) { 

    auto justPressed = PC::buttons.pressed(BTN_A);

    if (justPressed > 0 && this->counter > 0) {

        machine.changeState(GameStateType::TitleScreen); 

    }
    
    if (isFrameCount(12)) {
     
        this->counter++;
        
        if (this->counter == 4) {
            
            this->counter = 0;
            
        }
        
    }

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void SplashScreenState::render(StateMachine & machine) {

    PD::drawBitmap(38, 48, Images::Ppot[counter]);

}
