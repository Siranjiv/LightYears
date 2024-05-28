#pragma once
#include <box2d/b2_world.h>

#include "framework/Core.h"
namespace ly
{
	//We are using singleton for this
	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Get();
	protected:
		PhysicsSystem();
	private:
		static unique<PhysicsSystem> physicsSystem;
		b2World mPhysicsWorld;
		float mPhysicsScale;// We use this because the box2d physics engine uses meters as the size
	};
}