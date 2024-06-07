#include <box2d/b2_body.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"

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
	void PhysicsSystem::Step(float deltaTime)
	{
		ProcessPendingRemoveListeners();
		mPhysicsWorld.Step(deltaTime, mVelocityIterations, mPositionIterations);
	}

	//The System will figureout a physics body to generate the physics Body
	b2Body* PhysicsSystem::AddListener(Actor* listener)
	{
		//***This is done based on the documentation on how to setup a physics body***

		if (listener->IsPendingDestory()) return nullptr;

		//This is the definition of how the body is
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;

		//This pointer is the pointer that points to the listener actor
		//So we get a single when an event happens like overlapping or collition
		//"reinterpret_cast" is a type of casting operator used to convert one pointer type to another
		bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);
		bodyDef.position.Set(listener->GetActorLocation().x * GetPhysicsScale(), listener->GetActorLocation().y * GetPhysicsScale());

		//The Angle should be in radians
		bodyDef.angle = DegreesToRadians(listener->GetActorRotation());

		b2Body* body = mPhysicsWorld.CreateBody(&bodyDef);
		
		b2PolygonShape shape;
		auto bound = listener->GetActorGlobalBounds();
		shape.SetAsBox(bound.width/2.f * GetPhysicsScale(), bound.height / 2.f * GetPhysicsScale());

		//Fixture is the actual geometrical body of the physics body
		//And the Fixture needs to use that definition as it's shape here
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.isSensor = true;

		body->CreateFixture(&fixtureDef);

		return body;
	}

	void PhysicsSystem::RemoveListener(b2Body* bodyToRemove)
	{
		mPendingRemoveListeners.insert(bodyToRemove);
	}

	void PhysicsSystem::Cleanup()
	{
		physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
	}

	PhysicsSystem::PhysicsSystem()
		: mPhysicsWorld{ b2Vec2{0.f,0.f}},
		mPhysicsScale{0.01f},	// we use this to make it to centemeters
		mVelocityIterations{8},	//This is based on the documentation of box2d
		mPositionIterations{3},
		mContactListener{},
		mPendingRemoveListeners{}
	{
		mPhysicsWorld.SetContactListener(&mContactListener);
		mPhysicsWorld.SetAllowSleeping(false);
	}
	void PhysicsSystem::ProcessPendingRemoveListeners()
	{
		for (auto listener : mPendingRemoveListeners)
		{
			mPhysicsWorld.DestroyBody(listener);
		}

		mPendingRemoveListeners.clear();
	}
	void PhysicsContactListener::BeginContact(b2Contact* contact)
	{
		Actor* ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		Actor* ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if (ActorA && !ActorA->IsPendingDestory())
		{
			ActorA->OnActorBeginOverlap(ActorB);
		}

		if (ActorB && !ActorB->IsPendingDestory())
		{
			ActorB->OnActorBeginOverlap(ActorA);
		}

	}
	void PhysicsContactListener::EndContact(b2Contact* contact)
	{
		Actor* ActorA = nullptr;
		Actor* ActorB = nullptr;

		if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
		{
			ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		}

		if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
		{
			ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
		}

		if (ActorA && !ActorA->IsPendingDestory())
		{
			ActorA->OnActorEndOverlap(ActorB);
		}

		if (ActorB && !ActorB->IsPendingDestory())
		{
			ActorB->OnActorEndOverlap(ActorA);
		}
	}
}