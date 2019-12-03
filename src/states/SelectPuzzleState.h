#pragma once

#include "Pokitto.h"
#include "../utils/GameContext.h"
#include "../utils/GameState.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"
#include "../entities/Puzzle.h"
#include "BaseState.h"

class SelectPuzzleState : public BaseState {

  private:

    uint16_t puzzleIndex = 0;
    void populatePuzzle(StateMachine & machine, uint16_t puzzleIndex);

  public:
    void activate(StateMachine & machine) override;
    void update(StateMachine & machine) override;
    void render(StateMachine & machine) override;

};