#include "Pokitto.h"
#include "PokittoCookie.h"
#include "src/Game.h"
#include "src/entities/Puzzle.h"
#include "src/utils/GameCookie.h"


using PC = Pokitto::Core;
using PD = Pokitto::Display;


Game game;
GameCookie cookie;

int main() {


    // Initialise pokitto ..

    cookie.begin("PICROSS3", sizeof(cookie), (char*)&cookie);

    PC::begin();
    //PD::loadRGBPalette(palettePico);
    PD::loadRGBPalette(paletteCGA);
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

    