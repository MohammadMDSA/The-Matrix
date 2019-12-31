#pragma once

namespace Types
{

	public ref class Transform sealed
	{

	internal:
		DirectX::SimpleMath::Matrix GetWorldMatrix();
	private:
		DirectX::SimpleMath::Vector3 m_position;
		DirectX::SimpleMath::Vector3 m_rotation;
		DirectX::SimpleMath::Vector3 m_scale;

	};

}
