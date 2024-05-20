#include "weapon/BulletShooter.h"

namespace ly 
{
	BulletShooter::BulletShooter(Actor* owner, float cooldownTime)
		: Shooter{ owner },
		mCooldownClock{},
		mCooldownTime{ cooldownTime }
	{
	}
	bool BulletShooter::IsOnCooldown() const
	{
		return false;
	}
}