#pragma once

#include <stdint.h>

enum class GameStateType : uint8_t {
	SplashScreen,
	TitleScreen,
	SelectPuzzle, 
	PlayGame,
	GameOver
};

enum class GridValue : uint8_t {
	Blank = 0,
	Selected = 1,
	Marked = 2,
	SelectedInImage = 4,
};

enum class FilterValue : uint8_t {
	PlayerSelection = 3,
	SelectedInImage = 4
};
