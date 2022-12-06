#include "ATMath.h"
#include<math.h>
DirectX::XMFLOAT3 GetSpherePos(DirectX::XMFLOAT3 pos, float rotateXZ, float rotateY, DirectX::XMFLOAT3 centerPos)
{
	DirectX::XMFLOAT3 workPos=pos;
	//ïΩçsà⁄ìÆ
	workPos.x -= centerPos.x;
	workPos.y -= centerPos.y;
	workPos.z -= centerPos.z;

	float radius = sqrtf(workPos.x*workPos.x + workPos.y*workPos.y + workPos.z*workPos.z);

	workPos.x = sinf(rotateY)*sinf(rotateXZ)*radius;
	workPos.y = cosf(rotateY)*radius;
	workPos.z = sinf(rotateY)*cosf(rotateXZ)*radius;

	//ïΩçsà⁄ìÆ
	workPos.x += centerPos.x;
	workPos.y += centerPos.y;
	workPos.z += centerPos.z;


	return workPos;
}
