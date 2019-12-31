#include "pch.h"
#include "ObjectBase.h"

using namespace std;
using namespace Platform;
using namespace Platform::Collections;

Types::ObjectBase::ObjectBase()
{
	this->m_components = ref new Vector<Behaviour^>();
}

void Types::ObjectBase::AddComponent(ObjectComponentBase^ component)
{
	this->m_components->Append(component);
	component->SetObjectBase(this);
}
