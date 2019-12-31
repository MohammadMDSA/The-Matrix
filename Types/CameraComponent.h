#pragma once

#include "Behaviour.h"

namespace Types
{

	public ref class CameraComponent sealed : public Behaviour
	{
	public:
		virtual void Update();
		virtual void Setup();

	private:

	};

}

