#pragma once
#include"Geometory.h"
class Line
{
public:
	Line();
	~Line();
	void Update();
	void Draw();
	void Spawn(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2 );
	Info GetInfo();
	bool IsUse();
private:
	Info m_info;
	bool m_bUse=false;
	float m_life = 0.0f;
};

