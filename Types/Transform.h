#pragma once

namespace Types
{

	public ref class Transform sealed
	{

	internal:
		DirectX::SimpleMath::Matrix GetWorldMatrix();
	private:
		DirectX::SimpleMath::Vector3 Position;
		DirectX::SimpleMath::Vector3 Rotation;
		DirectX::SimpleMath::Vector3 Scale;

	};

}
