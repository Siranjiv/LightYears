#pragma once

namespace ly
{
	class Object
	{
	public:
		Object();
		virtual ~Object();
		
		void Destroy();
		bool IsPendingDestory() const { return mIsPendingDestory; }
	
	private:
		bool mIsPendingDestory;
	};
}