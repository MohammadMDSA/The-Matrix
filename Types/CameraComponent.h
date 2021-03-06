#pragma once

#include "ObjectComponentBase.h"
#include "Behaviour.h"
#include "ObjectBase.h"


namespace Types
{
	public ref class CameraComponent sealed : public IObjectComponentBase
	{
	public:

		virtual void Update();
		virtual void Setup();

		// Inherited via IObjectComponentBase
		virtual void SetObjectBase(Types::ObjectBase^ obj);
		virtual Types::ObjectBase^ SetObjectBase();

	private:
		Types::ObjectBase^ ObjectBase;
	};

}
