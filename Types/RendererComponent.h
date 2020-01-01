#pragma once

#include "ObjectComponentBase.h"
#include "Drawable.h"

namespace Types
{
	public ref class RendererComponent sealed : public IObjectComponentBase, public IDrawable
	{
	public:

		// Inherited via IObjectComponentBase
		virtual void Update();
		virtual void Setup();

		// Inherited via IDrawable
		virtual void Draw();

		// Inherited via IObjectComponentBase
		virtual void SetObjectBase(Types::ObjectBase^ obj);
		virtual Types::ObjectBase^ SetObjectBase();

	private:
		Types::ObjectBase^ ObjectBase;
	};

}
