#pragma once

namespace ly
{
	class Object
	{
	public:
		Object();
		virtual ~Object();
		
		virtual void Destroy();
		bool IsPendingDestory() const { return mIsPendingDestory; }
	
	private:
		bool mIsPendingDestory;
	};
}