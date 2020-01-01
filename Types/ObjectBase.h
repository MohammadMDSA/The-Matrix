#pragma once

#include "Behaviour.h"
#include "Transform.h"
#include "ObjectComponentBase.h"
#include "Drawable.h"


namespace Types
{
	interface class IObjectComponentBase;

	public ref class ObjectBase sealed : public IBehaviour
	{
	public:
		ObjectBase();

		void AddComponent(Types::IObjectComponentBase^ component);
		Types::Transform^ GetTransform();


		virtual void Update();
		virtual void Setup();

		// Inherited via IBehaviour
		virtual void SetObjectBase(ObjectBase^ obj);
		virtual ObjectBase^ SetObjectBase();

		Platform::Array<IDrawable^>^ GetDrawables();
		
	private:
		Types::Transform^ Transform;
		Platform::Collections::Vector<IBehaviour^>^ Components;
		Platform::Collections::Vector<Platform::String^>^ Tags;

	};
}
