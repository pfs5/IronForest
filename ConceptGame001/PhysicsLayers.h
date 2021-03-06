#pragma once
#include <vector>
#include <string>

/**
	Enables the engine to ignore collisions between certain objects in the game.
**/
namespace PhysicsLayers {
	const std::vector<std::string> layers = {"Default", "Arrow"};
	const std::vector<std::vector<bool>> layerIgnoreMatrix{ 
		{false, false},
		{false, true} 
	};
	
	int layerNumber(std::string _name);

	std::string layerName(int _number);
}