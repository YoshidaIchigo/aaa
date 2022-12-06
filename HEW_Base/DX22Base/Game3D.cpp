#include "Game3D.h"
#include "Geometory.h"
#include"CameraDebug.h"
#include"CameraPlayer.h"
#include"Input.h"
#include"CameraEvent.h"
#include "Main.h"

DirectX::XMFLOAT3 SubVector(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b);
bool CheckTriangleCollition(DirectX::XMFLOAT3 posA, DirectX::XMFLOAT3 posB, DirectX::XMFLOAT3 posC, DirectX::XMFLOAT3 TargetPos);

DirectX::XMFLOAT3 startPos = { 4.0f, 8.0f, 8.0f };
float time = 7.0f;
Game3D::Game3D()
{
	//頂点シェーダの読み込み
	m_pModelVS = new VertexShader;
	if (FAILED(m_pModelVS->Load("Assets/Shader/ModelVS.cso")))
		MessageBox(nullptr, "ModelVS.cso", "Error", MB_OK);

	//定数バッファの作成
	m_pWVP = new ConstantBuffer();
	m_pWVP->Create(sizeof(DirectX::XMFLOAT4X4) * 3);

	//モデルの作成
	//m_pModel = new Model();
	/*if (!m_pModel->Load("Assets/unitychan/unitychan/unitychan.fbx", 0.01f))
	{
		MessageBox(nullptr, "モデルエラー", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pModelVS);*/

	//ステージの作成
	m_pStage = new Stage();

	//楔の作成
	for (int i = 0; i < MAX_WEDGE; i++) { m_pWedges[i] = new Wedge(); }
	//CreateWedge(5.0f, 0.0f, 5.0f);
	//CreateWedge(-5.0f, 0.0f, 5.0f);
	//CreateWedge(-5.0f, 0.0f, -5.0f);
	//CreateWedge(5.0f, 0.0f, -5.0f);
	//ラインの作成
	for (int i = 0; i < MAX_LINE; i++) { m_pLines[i] = new Line(); }

	//敵の作成
	for (int i = 0; i < MAX_ENEMY; i++) { m_pEnemy[i] = new Enemy(); }

	//プレイヤーの生成
	m_pPlayer = new Player();

	//カメラの初期化
	m_mainCamera = CAM_PLAYER;
	m_pCamera[CAM_PLAYER] = new CameraPlayer(m_pPlayer);
	m_pCamera[CAM_DEBUG] = new CameraDebug();
	CameraEvent* pEvent= new CameraEvent();
	pEvent->SetEvent(startPos, m_pPlayer->GetPos(), time);
	m_pCamera[CAM_EVENT] = pEvent;
	m_pPlayer->SetCamera(m_pCamera[m_mainCamera]);

	InitGeometory();
}
Game3D::~Game3D()
{
	UninitGeometory();

	for (int i = 0; i < MAX_CAMERA; i++){ delete m_pCamera[i]; }
	
	delete m_pStage;
	//敵の削除
	for (int i = 0; i < MAX_ENEMY; i++) { delete m_pEnemy[i]; }
	//ラインの削除
	for (int i = 0; i < MAX_LINE; i++) { delete m_pLines[i]; }
	//楔の削除
	for (int i = 0; i < MAX_WEDGE; i++) { delete m_pWedges[i]; }

	//delete m_pModel;
	delete m_pWVP;
	delete m_pModelVS;
}
void Game3D::Update()
{
	UpdateGeometoryMatrix();

	//カメラの切り替え
	CameraKind camera = m_mainCamera;
	if (IsKeyPress('C')&& m_mainCamera != CAM_EVENT)//デバッグ用
	{
		if (IsKeyPress('1')) { camera = CAM_DEBUG; }
		if (IsKeyPress('2')) { camera = CAM_PLAYER; }
		if (IsKeyPress('3'))
		{
			CameraEvent* pEvent = reinterpret_cast<CameraEvent*>(m_pCamera[CAM_EVENT]);
			pEvent->SetEvent(startPos, m_pPlayer->GetPos(), time);
			camera = CAM_EVENT;
		}
		if (m_mainCamera != camera)
		{
			m_mainCamera = camera;
			m_pPlayer->SetCamera(m_pCamera[m_mainCamera]);
		}
	}

	//プレイヤーカメラのときのみプレイヤー更新
	if(m_mainCamera==CAM_PLAYER)
	{ m_pPlayer->Update(); }

	if (m_mainCamera == CAM_EVENT)
	{
		CameraEvent* pEvent = reinterpret_cast<CameraEvent*>(m_pCamera[m_mainCamera]);
		if (!pEvent->IsEvent())
		{
			m_mainCamera = CAM_PLAYER;
			m_pPlayer->SetCamera(m_pCamera[m_mainCamera]);
		}
	}
	m_pCamera[m_mainCamera]->Update();

	//楔の更新
	for (int i = 0; i < MAX_WEDGE; i++)
	{
		if (m_pWedges[i]->IsUse())
		{
			m_pWedges[i]->Update();
		}
	}
	//ラインの更新
	for (int i = 0; i < MAX_LINE; i++)
	{
		if (m_pLines[i]->IsUse())
		{
			m_pLines[i]->Update();
		}
	}

	//敵の更新
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (m_pEnemy[i]->IsUse())
		{
			m_pEnemy[i]->Update();
		}
	}

	if (IsKeyPress(VK_F1))
	{
		GetSceneManager()->StartSceneChange(SCENE_RESULT);
	}
}
void Game3D::Draw()
{
	/*//モデル表示
	//定数バッファの更新
	DirectX::XMFLOAT4X4 mat[3];

	//ワールド座標の計算
	//座標変換
	//移動　[0]に格納
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pModel->GetPos().x, m_pModel->GetPos().y, m_pModel->GetPos().z );

	//回転　[1]に格納
	//X回転
	DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(m_pModel->GetRotate().x);
	//Y回転
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(m_pModel->GetRotate().y);
	//Z回転
	DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(m_pModel->GetRotate().z);
	//拡大縮小　[2]に格納
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_pModel->GetScale().x,m_pModel->GetScale().y, m_pModel->GetScale().z);
	DirectX::XMMATRIX world = S * Rz * Ry * Rx * T;
	//転置行列へ変換
	world = DirectX::XMMatrixTranspose(world);
	//XMMATRIX型からXMFLOAT4X4型(mat[0])へ変換して格納
	DirectX::XMStoreFloat4x4(&mat[0], world);

	////ビュー行列の計算
	//DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(
	//	DirectX::XMVectorSet(0.0f, 1.5f, 3.0f, 0.0f),//カメラ座標
	//	DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f),//注視点
	//	DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) //カメラの上方向
	//);
	////転置行列へ変換
	//view = DirectX::XMMatrixTranspose(view);
	////XMMATRIX型からXMFLOAT4X4型(mat[0])へ変換して格納
	//DirectX::XMStoreFloat4x4(&mat[1], view);

	////プロジェクション行列の計算
	//DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(
	//	3.14f/3.0f,//カメラの縦方向の画角
	//	16.0f/9.0f,//縦幅に対する横幅の比の値
	//	0.1f,		//写り始めの距離
	//	2000.0f		//写す限界距離
	//);
	////転置行列へ変換
	//proj = DirectX::XMMatrixTranspose(proj);
	////XMMATRIX型からXMFLOAT4X4型(mat[0])へ変換して格納
	//DirectX::XMStoreFloat4x4(&mat[2], proj);

	//mat[1] = m_pCamera[m_mainCamera]->GetViewMatrix();
	//mat[2] = m_pCamera[m_mainCamera]->GetProjectionMatrix();

	*/
	//行列を定数バッファへ書き込み
	//m_pWVP->Write(mat);
	//m_pWVP->BindVS(0);
	//モデル表示
	//m_pModel->Draw();
	m_pPlayer->Draw();
	SetGeometoryVPMatrix(m_pCamera[m_mainCamera]->GetViewMatrix(), m_pCamera[m_mainCamera]->GetProjectionMatrix());
	//DrawBox();
	m_pStage->Draw();
	//DrawCylinder();
	//DrawCone();
	//DrawSphere();

	//楔の描画
	for (int i = 0; i < MAX_WEDGE; i++)
	{
		if (m_pWedges[i]->IsUse())
		{
			m_pWedges[i]->Draw();
		}
	}
	//ラインの描画
	for (int i = 0; i < MAX_LINE; i++)
	{
		if (m_pLines[i]->IsUse())
		{
			m_pLines[i]->Draw();
		}
	}
	//敵の描画
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (m_pEnemy[i]->IsUse())
		{
			m_pEnemy[i]->Draw();
		}
	}
}


void Game3D::CreateWedge(DirectX::XMFLOAT3 pos)
{
	for (int i = 0; i < MAX_WEDGE; i++)
	{
		if (!m_pWedges[i]->IsUse())
		{
			m_pWedges[i]->Spawn(pos);
			break;
		}
	}
}
void Game3D::CreateWedge(float x, float y, float z)
{
	DirectX::XMFLOAT3 pos{ x,y,z };
	for (int i = 0; i < MAX_WEDGE; i++)
	{
		if (!m_pWedges[i]->IsUse())
		{
			m_pWedges[i]->Spawn(pos);
			break;
		}
	}
}

void Game3D::CreateEnemy(DirectX::XMFLOAT3 pos)
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (!m_pEnemy[i]->IsUse())
		{
			m_pEnemy[i]->Spawn(pos);
			break;
		}
	}
}

void Game3D::CreateLine(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2)
{
	for (int i = 0; i < MAX_LINE; i++)
	{
		if (!m_pLines[i]->IsUse())
		{
			m_pLines[i]->Spawn(pos1,pos2);
			break;
		}
	}
}

void Game3D::TriggerWedge()
{
	DirectX::XMFLOAT3 centerPos{0.0f,0.0f,0.0f};
	int WedgesNo[MAX_WEDGE];
	int num = 0;
	for (int i = 0; i < MAX_WEDGE; i++)
	{
		if (m_pWedges[i]->IsUse())
		{
			centerPos.x += m_pWedges[i]->GetInfo().pos.x;
			centerPos.y = 0.0f;
			centerPos.z += m_pWedges[i]->GetInfo().pos.z;
			m_pWedges[i]->Trigger();
			WedgesNo[num] = i;
			num++;
			
		}
	}
	centerPos.x /= num;//平均を求める
	centerPos.z /= num;//

	if (num < 3) { return; }
	DirectX::XMFLOAT3 *vector=new DirectX::XMFLOAT3[num];
	//float rad[4];
	float *rad=new float[num];
	for (int i = 0; i < num; i++)
	{
		vector[i].x = m_pWedges[WedgesNo[i]]->GetInfo().pos.x - centerPos.x;
		vector[i].y = 0.0f;
		vector[i].z = m_pWedges[WedgesNo[i]]->GetInfo().pos.z - centerPos.z;
		rad[i] = atan2f(vector[i].x, vector[i].z);
		if (rad[i] < 0) { rad[i]+=3.1415f*2; }
	}
	//バブルソート小さい順
	float work1;
	int work2;
	//末尾から先頭のほうへ交換する処理
	for (int i = 0; i < num - 1; i++)
	{
		for (int j = num - 1; j > i; j--)
			//添え字jとiの比較
			if (rad[j - 1] > rad[j])
			{//j（末尾側）の方が小さければ値を交換
				work1 = rad[j - 1];
				rad[j - 1] = rad[j];
				rad[j] = work1;

				work2 = WedgesNo[j - 1];
				WedgesNo[j - 1] = WedgesNo[j];
				WedgesNo[j] = work2;
			}
	}

	//ラインを生成
	for (int i = 0; i < num-1; i++)
	{
		CreateLine(m_pWedges[WedgesNo[i]]->GetInfo().pos, m_pWedges[WedgesNo[i + 1]]->GetInfo().pos);
	}
	CreateLine(m_pWedges[WedgesNo[num - 1]]->GetInfo().pos, m_pWedges[WedgesNo[0]]->GetInfo().pos);
	//敵を検索
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (m_pEnemy[i]->IsUse())
		{
			DirectX::XMFLOAT3 posE = m_pEnemy[i]->GetInfo().pos;
			/*
			//当たり判定を取る三角形を探す
			DirectX::XMFLOAT3 vectorE;
			vectorE.x = posE.x - centerPos.x;
			vectorE.y =0.0f;
			vectorE.z = posE.z - centerPos.z;

			float radEnemy = atan2f(vectorE.x, vectorE.z);
			if (radEnemy < 0) { radEnemy += 3.1415f; }
			int j;
			for (j = 0; j < num; j++)
			{
				if (rad[j] > radEnemy)break;
			}
			DirectX::XMFLOAT3 posB;
			if (j == num) { 
				j--; posB = m_pWedges[WedgesNo[0]]->GetInfo().pos; }
			else if (j == 0) { 
				posB = m_pWedges[WedgesNo[num - 1]]->GetInfo().pos; }
			else { 
				posB = m_pWedges[WedgesNo[j - 1]]->GetInfo().pos; }
			DirectX::XMFLOAT3 posA = m_pWedges[WedgesNo[j]]->GetInfo().pos;
						if(CheckTriangleCollition(posA,posB,centerPos,posE))
			{
				//三角形の内側に点がある
				m_pEnemy[i]->Destroy();
			}
			else
			{
				//三角形の外側に点がある

			}

			*/
			bool bDestroy=false;
			for (int j = 0; j < num-1; j++)
			{
				DirectX::XMFLOAT3 posA = m_pWedges[WedgesNo[j]]->GetInfo().pos;
				DirectX::XMFLOAT3 posB = m_pWedges[WedgesNo[j+1]]->GetInfo().pos;
				if (CheckTriangleCollition(posA, posB, centerPos, posE))
				{
					//三角形の内側に点がある
					m_pEnemy[i]->Destroy();
					bDestroy = true;
				}
			}
			if (!bDestroy)
			{
				DirectX::XMFLOAT3 posA = m_pWedges[WedgesNo[0]]->GetInfo().pos;
				DirectX::XMFLOAT3 posB = m_pWedges[WedgesNo[num - 1]]->GetInfo().pos;
				if (CheckTriangleCollition(posA, posB, centerPos, posE))
				{
					//三角形の内側に点がある
					m_pEnemy[i]->Destroy();
				}
			}

		}
	}
}

//ベクトル引き算(a-b)
DirectX::XMFLOAT3 SubVector(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b)
{
	DirectX::XMFLOAT3 ret;
	ret.x = a.x - b.x;
	ret.z = a.z - b.z;
	ret.y = 0.0f;
	return ret;
}
bool CheckTriangleCollition(DirectX::XMFLOAT3 posA, DirectX::XMFLOAT3 posB, DirectX::XMFLOAT3 posC, DirectX::XMFLOAT3 TargetPos)
{
	//三角形の内側にあるか計算
	DirectX::XMFLOAT3 AB = SubVector(posB, posA);
	DirectX::XMFLOAT3 BP = SubVector(TargetPos, posB);

	DirectX::XMFLOAT3 BC = SubVector(posC, posB);
	DirectX::XMFLOAT3 CP = SubVector(TargetPos, posC);

	DirectX::XMFLOAT3 CA = SubVector(posA, posC);
	DirectX::XMFLOAT3 AP = SubVector(TargetPos, posA);

	//外積    Z成分だけ計算すればよいです
	double c1 = AB.x * BP.z - AB.z * BP.x;
	double c2 = BC.x * CP.z - BC.z * CP.x;
	double c3 = CA.x * AP.z - CA.z * AP.x;

	if ((c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0)) { return true; }
	return false;
}