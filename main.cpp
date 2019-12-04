#include "Pokitto.h"
#include "PokittoCookie.h"
#include "src/Game.h"
#include "src/entities/Puzzle.h"
#include "src/utils/GameCookie.h"


using PC = Pokitto::Core;
using PD = Pokitto::Display;


Game game;
GameCookie cookie;

const unsigned char pico8Palette[16*3] = {
  /*0,0,0,
    29,43,83,
    126,37,83,
    0,135,81,

    171,82,54,
    95,87,79,
    194,195,199,
    255,241,232,

    255,0,77,
    255,163,0,
    255,240,36,
    0,231,86,

    41,173,255,
    131,118,156,
    255,119,168,
    255,204,170*/
    
    0, 0, 0, 
95, 87, 79, 
194, 195, 199, 
255, 241, 232, 

255, 236, 39, 
255, 163, 0, 
255, 204, 170, 
171, 82, 54, 

255, 119, 168, 
255, 0, 77, 
131, 118, 156, 
126, 37, 83, 

41, 173, 255, 
29, 43, 83, 
0, 135, 81, 
0, 228, 54, 

};

int main() {


    // Initialise pokitto ..

    cookie.begin("PICROSS3", sizeof(cookie), (char*)&cookie);

    PC::begin();
    PD::loadRGBPalette(pico8Palette);
    PD::persistence = true;
    PD::invisiblecolor = 7;
    
    game.setup(&cookie);
    PD::setFont(font5x7);

    while (PC::isRunning()) {
    
    if (!PC::update()) continue;
    
        game.loop();
    
    }
    
    return 0;

}

    