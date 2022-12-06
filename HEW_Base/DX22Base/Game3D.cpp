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
	//���_�V�F�[�_�̓ǂݍ���
	m_pModelVS = new VertexShader;
	if (FAILED(m_pModelVS->Load("Assets/Shader/ModelVS.cso")))
		MessageBox(nullptr, "ModelVS.cso", "Error", MB_OK);

	//�萔�o�b�t�@�̍쐬
	m_pWVP = new ConstantBuffer();
	m_pWVP->Create(sizeof(DirectX::XMFLOAT4X4) * 3);

	//���f���̍쐬
	//m_pModel = new Model();
	/*if (!m_pModel->Load("Assets/unitychan/unitychan/unitychan.fbx", 0.01f))
	{
		MessageBox(nullptr, "���f���G���[", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pModelVS);*/

	//�X�e�[�W�̍쐬
	m_pStage = new Stage();

	//���̍쐬
	for (int i = 0; i < MAX_WEDGE; i++) { m_pWedges[i] = new Wedge(); }
	//CreateWedge(5.0f, 0.0f, 5.0f);
	//CreateWedge(-5.0f, 0.0f, 5.0f);
	//CreateWedge(-5.0f, 0.0f, -5.0f);
	//CreateWedge(5.0f, 0.0f, -5.0f);
	//���C���̍쐬
	for (int i = 0; i < MAX_LINE; i++) { m_pLines[i] = new Line(); }

	//�G�̍쐬
	for (int i = 0; i < MAX_ENEMY; i++) { m_pEnemy[i] = new Enemy(); }

	//�v���C���[�̐���
	m_pPlayer = new Player();

	//�J�����̏�����
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
	//�G�̍폜
	for (int i = 0; i < MAX_ENEMY; i++) { delete m_pEnemy[i]; }
	//���C���̍폜
	for (int i = 0; i < MAX_LINE; i++) { delete m_pLines[i]; }
	//���̍폜
	for (int i = 0; i < MAX_WEDGE; i++) { delete m_pWedges[i]; }

	//delete m_pModel;
	delete m_pWVP;
	delete m_pModelVS;
}
void Game3D::Update()
{
	UpdateGeometoryMatrix();

	//�J�����̐؂�ւ�
	CameraKind camera = m_mainCamera;
	if (IsKeyPress('C')&& m_mainCamera != CAM_EVENT)//�f�o�b�O�p
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

	//�v���C���[�J�����̂Ƃ��̂݃v���C���[�X�V
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

	//���̍X�V
	for (int i = 0; i < MAX_WEDGE; i++)
	{
		if (m_pWedges[i]->IsUse())
		{
			m_pWedges[i]->Update();
		}
	}
	//���C���̍X�V
	for (int i = 0; i < MAX_LINE; i++)
	{
		if (m_pLines[i]->IsUse())
		{
			m_pLines[i]->Update();
		}
	}

	//�G�̍X�V
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
	/*//���f���\��
	//�萔�o�b�t�@�̍X�V
	DirectX::XMFLOAT4X4 mat[3];

	//���[���h���W�̌v�Z
	//���W�ϊ�
	//�ړ��@[0]�Ɋi�[
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pModel->GetPos().x, m_pModel->GetPos().y, m_pModel->GetPos().z );

	//��]�@[1]�Ɋi�[
	//X��]
	DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(m_pModel->GetRotate().x);
	//Y��]
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(m_pModel->GetRotate().y);
	//Z��]
	DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(m_pModel->GetRotate().z);
	//�g��k���@[2]�Ɋi�[
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_pModel->GetScale().x,m_pModel->GetScale().y, m_pModel->GetScale().z);
	DirectX::XMMATRIX world = S * Rz * Ry * Rx * T;
	//�]�u�s��֕ϊ�
	world = DirectX::XMMatrixTranspose(world);
	//XMMATRIX�^����XMFLOAT4X4�^(mat[0])�֕ϊ����Ċi�[
	DirectX::XMStoreFloat4x4(&mat[0], world);

	////�r���[�s��̌v�Z
	//DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(
	//	DirectX::XMVectorSet(0.0f, 1.5f, 3.0f, 0.0f),//�J�������W
	//	DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f),//�����_
	//	DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) //�J�����̏����
	//);
	////�]�u�s��֕ϊ�
	//view = DirectX::XMMatrixTranspose(view);
	////XMMATRIX�^����XMFLOAT4X4�^(mat[0])�֕ϊ����Ċi�[
	//DirectX::XMStoreFloat4x4(&mat[1], view);

	////�v���W�F�N�V�����s��̌v�Z
	//DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(
	//	3.14f/3.0f,//�J�����̏c�����̉�p
	//	16.0f/9.0f,//�c���ɑ΂��鉡���̔�̒l
	//	0.1f,		//�ʂ�n�߂̋���
	//	2000.0f		//�ʂ����E����
	//);
	////�]�u�s��֕ϊ�
	//proj = DirectX::XMMatrixTranspose(proj);
	////XMMATRIX�^����XMFLOAT4X4�^(mat[0])�֕ϊ����Ċi�[
	//DirectX::XMStoreFloat4x4(&mat[2], proj);

	//mat[1] = m_pCamera[m_mainCamera]->GetViewMatrix();
	//mat[2] = m_pCamera[m_mainCamera]->GetProjectionMatrix();

	*/
	//�s���萔�o�b�t�@�֏�������
	//m_pWVP->Write(mat);
	//m_pWVP->BindVS(0);
	//���f���\��
	//m_pModel->Draw();
	m_pPlayer->Draw();
	SetGeometoryVPMatrix(m_pCamera[m_mainCamera]->GetViewMatrix(), m_pCamera[m_mainCamera]->GetProjectionMatrix());
	//DrawBox();
	m_pStage->Draw();
	//DrawCylinder();
	//DrawCone();
	//DrawSphere();

	//���̕`��
	for (int i = 0; i < MAX_WEDGE; i++)
	{
		if (m_pWedges[i]->IsUse())
		{
			m_pWedges[i]->Draw();
		}
	}
	//���C���̕`��
	for (int i = 0; i < MAX_LINE; i++)
	{
		if (m_pLines[i]->IsUse())
		{
			m_pLines[i]->Draw();
		}
	}
	//�G�̕`��
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
	centerPos.x /= num;//���ς����߂�
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
	//�o�u���\�[�g��������
	float work1;
	int work2;
	//��������擪�̂ق��֌������鏈��
	for (int i = 0; i < num - 1; i++)
	{
		for (int j = num - 1; j > i; j--)
			//�Y����j��i�̔�r
			if (rad[j - 1] > rad[j])
			{//j�i�������j�̕�����������Βl������
				work1 = rad[j - 1];
				rad[j - 1] = rad[j];
				rad[j] = work1;

				work2 = WedgesNo[j - 1];
				WedgesNo[j - 1] = WedgesNo[j];
				WedgesNo[j] = work2;
			}
	}

	//���C���𐶐�
	for (int i = 0; i < num-1; i++)
	{
		CreateLine(m_pWedges[WedgesNo[i]]->GetInfo().pos, m_pWedges[WedgesNo[i + 1]]->GetInfo().pos);
	}
	CreateLine(m_pWedges[WedgesNo[num - 1]]->GetInfo().pos, m_pWedges[WedgesNo[0]]->GetInfo().pos);
	//�G������
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (m_pEnemy[i]->IsUse())
		{
			DirectX::XMFLOAT3 posE = m_pEnemy[i]->GetInfo().pos;
			/*
			//�����蔻������O�p�`��T��
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
				//�O�p�`�̓����ɓ_������
				m_pEnemy[i]->Destroy();
			}
			else
			{
				//�O�p�`�̊O���ɓ_������

			}

			*/
			bool bDestroy=false;
			for (int j = 0; j < num-1; j++)
			{
				DirectX::XMFLOAT3 posA = m_pWedges[WedgesNo[j]]->GetInfo().pos;
				DirectX::XMFLOAT3 posB = m_pWedges[WedgesNo[j+1]]->GetInfo().pos;
				if (CheckTriangleCollition(posA, posB, centerPos, posE))
				{
					//�O�p�`�̓����ɓ_������
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
					//�O�p�`�̓����ɓ_������
					m_pEnemy[i]->Destroy();
				}
			}

		}
	}
}

//�x�N�g�������Z(a-b)
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
	//�O�p�`�̓����ɂ��邩�v�Z
	DirectX::XMFLOAT3 AB = SubVector(posB, posA);
	DirectX::XMFLOAT3 BP = SubVector(TargetPos, posB);

	DirectX::XMFLOAT3 BC = SubVector(posC, posB);
	DirectX::XMFLOAT3 CP = SubVector(TargetPos, posC);

	DirectX::XMFLOAT3 CA = SubVector(posA, posC);
	DirectX::XMFLOAT3 AP = SubVector(TargetPos, posA);

	//�O��    Z���������v�Z����΂悢�ł�
	double c1 = AB.x * BP.z - AB.z * BP.x;
	double c2 = BC.x * CP.z - BC.z * CP.x;
	double c3 = CA.x * AP.z - CA.z * AP.x;

	if ((c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0)) { return true; }
	return false;
}