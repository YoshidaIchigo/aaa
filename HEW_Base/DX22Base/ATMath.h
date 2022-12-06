#pragma once
#include"DirectX.h"
#include <DirectXMath.h>
DirectX::XMFLOAT3 GetSpherePos(DirectX::XMFLOAT3 pos, float rotateXZ, float rotateY,
	DirectX::XMFLOAT3 centerPos = { 0.0f, 0.0f, 0.0f});
//DirectX::XMFLOAT3 GetSpherePos(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rotate);

