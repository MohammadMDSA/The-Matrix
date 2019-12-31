#pragma once

#include "Behaviour.h"
#include "ObjectBase.h"

ref class ObjectBase;
namespace Types
{

	ref class ObjectComponentBase abstract : public Behaviour
	{

	public:
		// Inherited via Behaviour
		virtual void Update() abstract;
		virtual void Setup() abstract;
		void SetObjectBase(Types::ObjectBase^ object);

	protected private:
		ObjectBase^ ObjectBase;
	};

}
