#include "player/PlayerSpaceship.h"

namespace ly 
{
	PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& path)
		:Spaceship{owningWorld, path}
	{
	}
}