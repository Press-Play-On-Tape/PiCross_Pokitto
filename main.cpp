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

    cookie.begin("PICROSS", sizeof(cookie), (char*)&cookie);

    Pokitto::Sound::playMusicStream("thechase.raw",0);

    PC::begin();
    PD::loadRGBPalette(palettePico);
    PD::invisiblecolor = 2;
    PD::persistence = true;

    game.setup(&cookie);
    PD::setFont(font5x7);

    while (PC::isRunning()) {
    
    if (!PC::update()) continue;
    
//        PC::sound.updateStream();
        game.loop();
    
    }
    
    return 0;

}

    