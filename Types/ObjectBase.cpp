#include "pch.h"
#include "ObjectBase.h"

using namespace std;
using namespace Platform;
using namespace Platform::Collections;
using namespace Types;

Types::ObjectBase::ObjectBase()
{
	this->Components = ref new Vector<IBehaviour^>();
}

void Types::ObjectBase::AddComponent(IObjectComponentBase^ component)
{
	this->Components->Append(component);
	component->SetObjectBase(this);
}

Types::Transform^ Types::ObjectBase::GetTransform()
{
	return this->Transform;
}

void Types::ObjectBase::Update()
{
	for(Types::IBehaviour^ var : this->Components)
	{
		var->Update();
	}
}

void Types::ObjectBase::Setup()
{
	for (Types::IBehaviour^ var : this->Components)
	{
		var->Setup();
	}
}

Platform::Array<IDrawable^>^ Types::ObjectBase::GetDrawables()
{
	auto result = ref new Platform::Collections::Vector<IDrawable^>();
	for (Types::IBehaviour^ var : this->Components)
	{
		auto comp = dynamic_cast<IDrawable^>(var);
		if (comp)
		{
			result->Append(comp);
		}
	}

	auto arr = ref new Platform::Array<IDrawable^>(result->Size);

	for (int i = 0; i < result->Size; i++)
	{
		arr[i] = result->GetAt(i);
	}

	return arr;
}

void Types::ObjectBase::SetObjectBase(ObjectBase^ obj)
{
	return;
}

ObjectBase^ Types::ObjectBase::SetObjectBase()
{
	return this;
}
