#pragma once
#include <SFML/System.hpp>
#include "weapon/Shooter.h"

namespace ly 
{
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(Actor* owner, float cooldownTime = 1.f);
		virtual bool IsOnCooldown() const override;
	private:
		sf::Clock mCooldownClock;//Cool Down Mechanic
		float mCooldownTime;
	};
}