#pragma once

namespace Images {
    
    #include "QuestionMark.h"
    #include "Selector_Top.h"
    #include "Selector_Bottom.h"
    #include "Box.h"
    #include "ArrowUp.h"
    #include "ArrowDown.h"
    #include "Congratulations.h"
    #include "LeaveGame.h"
    #include "Cursor.h"
    #include "Binder_Top.h"
    #include "Binder_Bottom.h"
    #include "Pen.h"
    #include "PiCrossHeading.h"

    #include "ppot/Ppot_00.h"
    #include "ppot/Ppot_01.h"
    #include "ppot/Ppot_02.h"
    #include "ppot/Ppot_03.h"

    #include "title/TitleScreen_Bottom.h"
    #include "title/TitleScreen_Middle.h"
    #include "title/TitleScreen_Top.h"

    const uint8_t * const Ppot[] = { 
        
        Ppot_00, Ppot_01, Ppot_02, Ppot_03,
        
    };

}
