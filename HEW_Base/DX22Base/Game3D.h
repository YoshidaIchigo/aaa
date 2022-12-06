#ifndef __GAME_3D_H__
#define __GAME_3D_H__
#include"Model.h"
#include"ConstantBuffer.h"
#include"Stage.h"
#include"CameraBase.h"
#include"Player.h"
#include"Wedge.h"
#include"Line.h"
#include<DirectXMath.h>
#include"Enemy.h"

#define MAX_WEDGE (40)
#define MAX_LINE (40)
#define MAX_ENEMY (20)

enum CameraKind
{
	CAM_PLAYER,
	CAM_DEBUG,
	CAM_EVENT,
	MAX_CAMERA//カメラ最大数
};

class Game3D
{
public:
	Game3D();
	~Game3D();

	void Update();
	void Draw();
	void CreateWedge(DirectX::XMFLOAT3 pos);
	void CreateWedge(float x, float y, float z);
	void CreateEnemy(DirectX::XMFLOAT3 pos);
	void CreateLine(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2);
	void TriggerWedge();
	
private:
	//Model* m_pModel;
	VertexShader* m_pModelVS;
	Stage* m_pStage;
	CameraBase* m_pCamera[MAX_CAMERA];//複数台用意
	CameraKind m_mainCamera;//現在利用しているカメラの番号
	Player* m_pPlayer;
	ConstantBuffer* m_pWVP;
	Wedge* m_pWedges[MAX_WEDGE];
	Line* m_pLines[MAX_LINE];
	Enemy* m_pEnemy[MAX_ENEMY];
};

#endif // __GAME_3D_H__