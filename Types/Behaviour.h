#pragma once

#include "pch.h"

namespace Types
{
	ref class ObjectBase;

	public interface class IBehaviour
	{
	public:

		virtual void Update();
		virtual void Setup();

		virtual void SetObjectBase(ObjectBase^ obj);
		virtual ObjectBase^ SetObjectBase();


	};

}
