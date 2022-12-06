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
	float m_radXZ,m_radY;//�ڕW�p�x
	float m_lateXZ, m_lateY;//�ڕW�ʒu�ɑ΂��Ēx��Ă��Ă����p�x(���݊p�x)
	float m_radius;
};

