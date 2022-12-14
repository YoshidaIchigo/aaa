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
	float m_radXZ,m_radY;//目標角度
	float m_lateXZ, m_lateY;//目標位置に対して遅れてついていく角度(現在角度)
	float m_radius;
};

