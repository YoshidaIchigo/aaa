#pragma once
#include "CameraBase.h"
#include"Player.h"
class CameraPlayer :
	public CameraBase
{
public:
	CameraPlayer(Player* pPlayer);
	~CameraPlayer(){}
	void Update();
private:
	Player* m_pPlayer;
	float m_radXZ,m_radY;//–Ú•WŠp“x
	float m_lateXZ, m_lateY;//–Ú•WˆÊ’u‚É‘Î‚µ‚Ä’x‚ê‚Ä‚Â‚¢‚Ä‚¢‚­Šp“x(Œ»İŠp“x)
	float m_radius;
};

