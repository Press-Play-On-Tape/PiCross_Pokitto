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

// 0, 0, 0, 
// 255, 241, 232,          // Light beige          01
// 255, 119, 168,          // Bright Pink
// 41, 173, 255,           // Bright Blue          03

// 194, 195, 199,          // Light Grey           04
// 255, 163, 0,            // Bright Orange
// 255, 204, 170,          // Skin 
// 171, 82, 54,            // Orange / Brown

// 95, 87, 79,             // Dark Brown           08  
// 255, 0, 77,             // Bright Red
// 131, 118, 156,          // Lilac
// 0, 135, 81,             // Dark Green           11

// 255, 236, 39,           // Bright Yellow
// 29, 43, 83,             // Dark Blue
// 126, 37, 83,            // Dark Mauve
// 0, 228, 54,             // Bright Green



0, 0, 0,                // Black                00
255, 241, 232,          // Off White            01
255, 119, 168,          // Bright Pink
41, 173, 255,           // Bright Blue          03

194, 195, 199,          // Light Grey           04
255, 163, 0,            // Bright Orange
255, 204, 170,          // Skin 
255, 0, 77,             // Bright Red

95, 87, 79,             // Dark Brown / Grey    08  
171, 82, 54,            // Orange / Brown
131, 118, 156,          // Lilac
0, 135, 81,             // Dark Green           11

255, 236, 39,           // Bright Yellow
29, 43, 83,             // Dark Blue
126, 37, 83,            // Dark Mauve
0, 228, 54,             // Bright Green
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

    