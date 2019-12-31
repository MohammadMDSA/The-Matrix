#pragma once

#include "Behaviour.h"
#include "Transform.h"
#include "ObjectComponentBase.h"

namespace Types
{

	public ref class ObjectBase sealed
	{
	public:
		ObjectBase();

		void AddComponent(ObjectComponentBase^ component);
		
	private:
		Platform::Collections::Vector<Behaviour^>^ m_components;
		Platform::String^ m_name;
		Platform::Collections::Vector<Platform::String^>^ m_tags;
		Types::Transform^ Transform;
	};
}
