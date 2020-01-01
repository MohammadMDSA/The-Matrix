#include "pch.h"
#include "CameraComponent.h"

void Types::CameraComponent::Update()
{
	
}

void Types::CameraComponent::Setup()
{
	
}

void Types::CameraComponent::SetObjectBase(Types::ObjectBase^ obj)
{
	this->ObjectBase = obj;
}

Types::ObjectBase^ Types::CameraComponent::SetObjectBase()
{
	return this->ObjectBase;
}
