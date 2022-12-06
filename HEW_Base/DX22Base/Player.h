#pragma once
#include"CameraBase.h"
#include"Shader.h"
#include"Model.h"
#include"ConstantBuffer.h"
class Player
{
public:
	Player();
	~Player();
	void Update();
	void Draw();
	void SetCamera(CameraBase* pCamera) { m_pCamera=pCamera; }
	DirectX::XMFLOAT3 GetPos() { return m_pos; }
private:
	void UpdateStatus();
	CameraBase* m_pCamera;
	DirectX::XMFLOAT3 m_pos;
	Model* m_pModel;
	VertexShader* m_pVS;
	//VertexShader* m_pPS;
	ConstantBuffer* m_pWVP;
};

