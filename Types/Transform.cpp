#include "pch.h"
#include "Transform.h"

using namespace DirectX::SimpleMath;

Matrix Types::Transform::GetWorldMatrix()
{
	auto translation = Matrix::CreateTranslation(this->Position);
	auto scale = Matrix::CreateScale(this->Scale);
	auto rotation = Matrix::CreateFromYawPitchRoll(this->Rotation.y, this->Rotation.x, this->Rotation.z);

	return Matrix::Identity * scale * rotation * translation;
}
