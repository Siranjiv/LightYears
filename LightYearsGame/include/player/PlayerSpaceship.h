#pragma once
#include "spaceship/Spaceship.h"

namespace ly
{
	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* owningWorld, const std::string& path="SpaceShooterRedux/PNG/playerShip1_blue.png");
	};
}