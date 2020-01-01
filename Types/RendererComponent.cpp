#include "pch.h"
#include "RendererComponent.h"

void Types::RendererComponent::Update()
{
	
}

void Types::RendererComponent::Setup()
{
	throw ref new Platform::NotImplementedException();
}

void Types::RendererComponent::Draw()
{
	throw ref new Platform::NotImplementedException();
}



void Types::RendererComponent::SetObjectBase(Types::ObjectBase^ obj)
{
	this->ObjectBase = obj;
}

Types::ObjectBase^ Types::RendererComponent::SetObjectBase()
{
	return this->ObjectBase;
}
