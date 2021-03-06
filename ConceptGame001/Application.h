#pragma once

#include <stack>

#include "GameState.h"

/**
	Main application class holding the whole game and game loop.
**/
class Application {
public:
	Application();
	~Application();

	/**
		Runs the main game loop
	**/
	void runMainLoop();

	/**
		Adds a game state to the application
		@param _gameState pointer to gamestate allocated on dynamic storage.
		Application handles memory deallocation.
	**/
	void addGameState(GameState *_gameState);

	/**
		Removes the last game state and switches to the previous one.
	**/
	void popGameState();
};