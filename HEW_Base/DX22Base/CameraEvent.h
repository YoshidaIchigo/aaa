#pragma once
#include "CameraBase.h"
class CameraEvent :
	public CameraBase
{
public:
	CameraEvent();
	~CameraEvent(){}
	void Update();
	void SetEvent(DirectX::XMFLOAT3 startPos, DirectX::XMFLOAT3 endPos, float time);
	bool IsEvent() { return m_time < m_totalTime; }
private:
	DirectX::XMFLOAT3 m_start;
	DirectX::XMFLOAT3 m_end;
	float m_time;
	float m_totalTime;
};

