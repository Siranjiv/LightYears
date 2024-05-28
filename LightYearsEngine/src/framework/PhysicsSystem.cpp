#include "framework/PhysicsSystem.h"

namespace ly
{
	//The static needs a starting value
	unique<PhysicsSystem> PhysicsSystem::physicsSystem{ nullptr };//Will get a link error without this line since declared as static

	PhysicsSystem& PhysicsSystem::Get()
	{
		if (!physicsSystem)
		{
			physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
		}

		return *physicsSystem;
	}
	PhysicsSystem::PhysicsSystem()
		: mPhysicsWorld{ b2Vec2{0.f,0.f}},
		mPhysicsScale{0.01f}	// we use this to make it to centemeters
	{

	}
}