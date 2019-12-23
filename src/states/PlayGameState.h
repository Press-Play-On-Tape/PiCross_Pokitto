#pragma once

#include "../utils/GameContext.h"
#include "../utils/GameState.h"
#include "../utils/Enums.h"
#include "../images/Images.h"
#include "../entities/Entities.h"
#include "../utils/Utils.h"
#include "BaseState.h"

class PlayGameState : public BaseState {

    private:

    enum class ViewState : uint8_t {
    	Normal,
    	GameOver,
    	Menu, 
    	Hint
    };

    enum class HintType : uint8_t {
    	Col,
    	Row
    };


  public:	
  
    void activate(StateMachine & machine) override;
    void update(StateMachine & machine) override;
    void render(StateMachine & machine) override;

  private:

    ViewState viewState = ViewState::Normal;
    
    uint8_t maxSeriesRow = 0;
    uint8_t maxSeriesCol = 0;
    uint8_t marginTop = 0;
    uint8_t marginLeft = 0;
    uint8_t puzzleTop = 0;
    uint8_t puzzleLeft = 0;

    bool showHintGraphic = false;

    uint8_t counter = 0;
    uint8_t xOffset = 0;
    uint8_t yOffset = 0;
    uint8_t menuOption = 0;
    uint8_t flashCount = 0;
    
    HintType hintType = HintType::Col;
    uint8_t hintIndexCol = 0;
    uint8_t hintIndexRow = 0;

    GridValue lastUpdate = GridValue::Blank;
};




