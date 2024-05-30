#pragma once
#include <box2d/b2_world.h>

#include "framework/Core.h"
namespace ly
{
	class Actor;
	//We are using singleton for this
	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Get();
		void Step(float deltaTime);
		b2Body* AddListener(Actor* listener);
		float GetPhysicsScale() const { return mPhysicsScale; }
	protected:
		PhysicsSystem();
	private:
		static unique<PhysicsSystem> physicsSystem;
		b2World mPhysicsWorld;
		float mPhysicsScale;// We use this because the box2d physics engine uses meters as the size
		int mVelocityIterations;
		int mPositionIterations;
	};
}