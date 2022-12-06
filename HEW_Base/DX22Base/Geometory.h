#ifndef __GEOMETORY_H__
#define __GEOMETORY_H__

#include "DirectX.h"
#include <DirectXMath.h>

struct Info
{
	DirectX::XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	DirectX::XMFLOAT3 size = { 1.0f, 1.0f, 1.0f };
	DirectX::XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
};
HRESULT InitGeometory();
void UninitGeometory();
void SetGeometoryTranslate(float x, float y, float z);
void SetGeometoryRotation(float x, float y, float z);
void SetGeometoryScaling(float x, float y, float z);
void SetGeometoryTranslate(DirectX::XMFLOAT3);
void SetGeometoryRotation(DirectX::XMFLOAT3);
void SetGeometoryScaling(DirectX::XMFLOAT3);

void SetGeometoryVPMatrix(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj);
void DrawBox();
void DrawSphere();
void DrawCylinder();
void DrawCone();
void DrawCapsule();
void DrawArrow();
void UpdateGeometoryMatrix();

#endif // __GEOMETORY_H__