#include "pch.h"
#include "Transform.h"

using namespace DirectX::SimpleMath;

Matrix Types::Transform::GetWorldMatrix()
{
	auto translation = Matrix::CreateTranslation(this->m_position);
	auto scale = Matrix::CreateScale(this->m_scale);
	auto rotation = Matrix::CreateFromYawPitchRoll(this->m_rotation.y, this->m_rotation.x, this->m_rotation.z);

	return Matrix::Identity * scale * rotation * translation;
}
