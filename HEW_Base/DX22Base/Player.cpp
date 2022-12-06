#include "Player.h"
#include"Input.h"
#include"Game3D.h"
#include"Main.h"
const float PLAYER_MOVE_SPEAD=0.1f;

Player::Player()
	:m_pos(0.0f, 0.5f, 0.0f)
{
	//モデルの生成
	m_pModel = new Model();
	if (!m_pModel->Load("Assets/unitychan/unitychan/unitychan.fbx", 0.01f))
	{
		MessageBox(nullptr, "モデルエラー", "Error", MB_OK);
	}
	//シェーダの読み込み
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/ModelVS.cso")))
		MessageBox(nullptr, "ModelVS.cso", "Error", MB_OK);
	m_pModel->SetVertexShader(m_pVS);
	//定数バッファの作成
	m_pWVP = new ConstantBuffer();
	m_pWVP->Create(sizeof(DirectX::XMFLOAT4X4) * 3);
}

Player::~Player()
{
	delete m_pWVP;
	delete m_pVS;
	delete m_pModel;
}

void Player::Update()
{
	UpdateStatus();
	if (IsKeyTrigger(VK_SPACE))
	{
		GetSceneManager()->GetGame()->CreateWedge(m_pos);
	}
	if (IsKeyTrigger(VK_RETURN))
	{
		GetSceneManager()->GetGame()->TriggerWedge();
	}
	if (IsKeyTrigger(VK_LSHIFT))
	{
		GetSceneManager()->GetGame()->CreateEnemy(m_pos);
	}
}

void Player::Draw()
{
	if (!m_pCamera) { return; }
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMStoreFloat4x4(&mat[0], 
		DirectX::XMMatrixTranspose( DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)));
	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();
	m_pWVP->Write(mat);
	m_pWVP->BindVS(0);
	m_pModel->Draw();
}

void Player::UpdateStatus()
{
	DirectX::XMFLOAT3 camPos = m_pCamera->GetPos();
	camPos.y = 0.0f;
	DirectX::XMFLOAT3 camLook = m_pCamera->GetLook();
	camLook.y = 0.0f;
	DirectX::XMVECTOR vCanPos = DirectX::XMLoadFloat3(&camPos);
	DirectX::XMVECTOR vCanLook = DirectX::XMLoadFloat3(&camLook);



	DirectX::XMVECTOR vFront;
	vFront = DirectX::XMVectorSubtract(vCanLook, vCanPos);//前 − 後ろ
	vFront = DirectX::XMVector3Normalize(vFront);


	DirectX::XMMATRIX matRotSide = DirectX::XMMatrixRotationY(3.14f*0.5); //Y軸90度回転
	DirectX::XMVECTOR vSide = DirectX::XMVector3TransformCoord(vFront, matRotSide);



	DirectX::XMVECTOR vMove = DirectX::XMVectorZero();


	if (IsKeyPress('W')) { vMove = DirectX::XMVectorAdd(vMove, vFront); }
	if (IsKeyPress('S')) { vMove = DirectX::XMVectorSubtract(vMove, vFront); }
	if (IsKeyPress('D')) { vMove = DirectX::XMVectorAdd(vMove, vSide); }
	if (IsKeyPress('A')) { vMove = DirectX::XMVectorSubtract(vMove, vSide); }
	//if (IsKeyPress('E')) { m_pos.y += PLAYER_MOVE_SPEAD; }
	//if (IsKeyPress('Q')) { m_pos.y -= PLAYER_MOVE_SPEAD; }


	vMove = DirectX::XMVectorScale(vMove, PLAYER_MOVE_SPEAD);

	DirectX::XMFLOAT3 move;
	DirectX::XMStoreFloat3(&move, vMove);
	m_pos.x += move.x; m_pos.y += move.y; m_pos.z += move.z;
}

