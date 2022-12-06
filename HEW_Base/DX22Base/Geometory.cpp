#include "Geometory.h"
#include "MeshBuffer.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include"ATMath.h"
//--- マクロ
#define GEOMETORY_SAFE_DELETE(p) if(p){delete p; p = nullptr;}

//--- 定数
const int GEOMETORY_SPLIT = 16;
const int GEOMETORY_SPLIT_VTX_X = GEOMETORY_SPLIT + 1;
const int GEOMETORY_SPLIT_VTX_Y = GEOMETORY_SPLIT / 2 + 1;
const int GEOMETORY_SPLIT_IDX_X = GEOMETORY_SPLIT;
const int GEOMETORY_SPLIT_IDX_Y = GEOMETORY_SPLIT / 2;

//--- 構造体
struct GeometoryVertex
{
	float pos[3];
	float uv[2];
};

//--- プロトタイプ宣言
void CreateGeometoryBox();
void CreateGeometorySphere();
void CreateGeometoryCylinder();
void CreateGeometoryCapsule();
void CreateGeometoryCone();
void CreateGeometoryArrow();
void CreateGeometoryShader();
void CreateGeometoryConstantBuffer();

//--- グローバル変数
MeshBuffer* g_pGeometoryBox;
MeshBuffer* g_pGeometorySphere;
MeshBuffer* g_pGeometoryCylinder;
MeshBuffer* g_pGeometoryCapsule;
MeshBuffer* g_pGeometoryCone;
MeshBuffer* g_pGeometoryArrow;
VertexShader* g_pGeometoryVS;
PixelShader* g_pGeometoryPS;
ConstantBuffer* g_pGeometoryWVP;
DirectX::XMFLOAT4X4 g_geometoryMat[3];
DirectX::XMFLOAT3 g_geometoryTransform[3];

HRESULT InitGeometory()
{
	CreateGeometoryShader();
	CreateGeometoryConstantBuffer();
	CreateGeometoryBox();
	CreateGeometorySphere();
	CreateGeometoryCylinder();
	//CreateGeometoryCapsule();
	CreateGeometoryCone();
	//CreateGeometoryArrow();

	SetGeometoryTranslate(0.0f, 0.0f, 0.0f);
	
	return S_OK;
}
void UninitGeometory()
{
	GEOMETORY_SAFE_DELETE(g_pGeometoryCone);
	//GEOMETORY_SAFE_DELETE(g_pGeometoryCapsule);
	GEOMETORY_SAFE_DELETE(g_pGeometoryCylinder);
	//GEOMETORY_SAFE_DELETE(g_pGeometorySphere);
	GEOMETORY_SAFE_DELETE(g_pGeometoryBox);
	GEOMETORY_SAFE_DELETE(g_pGeometoryPS);
	GEOMETORY_SAFE_DELETE(g_pGeometoryVS);
}
void SetGeometoryTranslate(float x, float y, float z)
{
	g_geometoryTransform[0] = DirectX::XMFLOAT3(x, y, z);
}
void SetGeometoryTranslate(DirectX::XMFLOAT3 transform)
{
	g_geometoryTransform[0] = transform;
}
void SetGeometoryRotation(float x, float y, float z)
{
	g_geometoryTransform[1] = DirectX::XMFLOAT3(x, y, z);
}
void SetGeometoryRotation(DirectX::XMFLOAT3 rotation)
{
	g_geometoryTransform[1] = rotation;
}
void SetGeometoryScaling(float x, float y, float z)
{
	g_geometoryTransform[2] = DirectX::XMFLOAT3(x, y, z);
}
void SetGeometoryScaling(DirectX::XMFLOAT3 scale)
{
	g_geometoryTransform[2] = scale;
}
void SetGeometoryVPMatrix(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj)
{
	g_geometoryMat[1] = view;
	g_geometoryMat[2] = proj;
}
void DrawBox()
{
	UpdateGeometoryMatrix();
	g_pGeometoryVS->Bind();
	g_pGeometoryPS->Bind();
	g_pGeometoryWVP->BindVS(0);
	g_pGeometoryBox->Draw();
}
void DrawSphere()
{
	UpdateGeometoryMatrix();
	g_pGeometoryVS->Bind();
	g_pGeometoryPS->Bind();
	g_pGeometoryWVP->BindVS(0);
	g_pGeometorySphere->Draw();
}
void DrawCylinder()
{
	UpdateGeometoryMatrix();
	g_pGeometoryVS->Bind();
	g_pGeometoryPS->Bind();
	g_pGeometoryWVP->BindVS(0);
	g_pGeometoryCylinder->Draw();
}
void DrawCone()
{
	UpdateGeometoryMatrix();
	g_pGeometoryVS->Bind();
	g_pGeometoryPS->Bind();
	g_pGeometoryWVP->BindVS(0);
	g_pGeometoryCone->Draw();
}
void DrawCapsule()//5
{
	UpdateGeometoryMatrix();
	g_pGeometoryVS->Bind();
	g_pGeometoryPS->Bind();
	g_pGeometoryWVP->BindVS(0);
	g_pGeometoryCapsule->Draw();
}
void DrawArrow()//5
{
	UpdateGeometoryMatrix();
	g_pGeometoryVS->Bind();
	g_pGeometoryPS->Bind();
	g_pGeometoryWVP->BindVS(0);
	g_pGeometoryArrow->Draw();
}



void CreateGeometoryBox()//1
{
	//-----
	// 01-3D図形を参考に作成
	//-----

	GeometoryVertex vtx[] = {
		//-Z面
		{{-0.5f, 0.5f,-0.5f},{0.0f,0.0f}},
		{{ 0.5f, 0.5f,-0.5f},{1.0f,0.0f}},
		{{-0.5f,-0.5f,-0.5f},{0.0f,1.0f}},
		{{ 0.5f,-0.5f,-0.5f},{1.0f,1.0f}},

		//+X面
		{{ 0.5f, 0.5f,-0.5f},{0.0f,0.0f}},
		{{ 0.5f, 0.5f, 0.5f},{1.0f,0.0f}},
		{{ 0.5f,-0.5f,-0.5f},{0.0f,1.0f}},
		{{ 0.5f,-0.5f, 0.5f},{1.0f,1.0f}},

		//+Z面
		{{ 0.5f, 0.5f, 0.5f},{0.0f,0.0f}},
		{{-0.5f, 0.5f, 0.5f},{1.0f,0.0f}},
		{{ 0.5f,-0.5f, 0.5f},{0.0f,1.0f}},
		{{-0.5f,-0.5f, 0.5f},{1.0f,1.0f}},

		//-X面
		{{-0.5f, 0.5f, 0.5f},{0.0f,0.0f}},
		{{-0.5f, 0.5f,-0.5f},{1.0f,0.0f}},
		{{-0.5f,-0.5f, 0.5f},{0.0f,1.0f}},
		{{-0.5f,-0.5f,-0.5f},{1.0f,1.0f}},

		//+Y面
		{{ 0.5f, 0.5f,-0.5f},{0.0f,0.0f}},
		{{-0.5f, 0.5f,-0.5f},{1.0f,0.0f}},
		{{ 0.5f, 0.5f, 0.5f},{0.0f,1.0f}},
		{{-0.5f, 0.5f, 0.5f},{1.0f,1.0f}},

		//-Y面
		{{ 0.5f,-0.5f, 0.5f},{0.0f,0.0f}},
		{{-0.5f,-0.5f, 0.5f},{1.0f,0.0f}},
		{{ 0.5f,-0.5f,-0.5f},{0.0f,1.0f}},
		{{-0.5f,-0.5f,-0.5f},{1.0f,1.0f}},
	};

	int idx[] = {
		0,1,2,2,1,3,		//-Z面
		4,5,6,6,5,7,		//+X面
		8,9,10,10,9,11,		//+Z面
		12,13,14,14,13,15,	//-X面
		16,17,18,18,17,19,	//+Y面
		20,21,22,22,21,23	//-Y面
	};


	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = 24;
	desc.vtxSize = 20;//sizeof(GeometoryVertex);
	desc.pIdx = idx;
	desc.idxCount = 36;
	desc.idxSize = 4;// sizeof(int);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	g_pGeometoryBox = new MeshBuffer(desc);
}
void CreateGeometorySphere()//4
{
	const int spritHeight = 5;//高さの分割数
	const int spritShaft = 10;//軸回りの分割数
	const int idxNum = (spritHeight+1) * spritShaft * 6;
	const DirectX::XMFLOAT3 posBase = { 0.0f,0.5f,0.0f };
	GeometoryVertex vtx[(spritHeight+1) * spritShaft*4] = {};
	int idx[idxNum] = {};
	int vtxNum=0;//引数
	for (int i = 0; i < spritHeight+1; i++)
	{
		float PI = 3.141592f;
		//高さの計算
		float radianY1 = PI * float(i)* 1.0f / (float)(spritHeight+1);
		float radianY2 = PI * float(i+1)*1.0f / (float)(spritHeight+1);
		//DirectX::XMFLOAT3 posBaseY1 = GetSpherePos(posBase, 0.0f, radianY1);
		//DirectX::XMFLOAT3 posBaseY2 = GetSpherePos(posBase, 0.0f, radianY2);


		for (int j = 0; j < spritShaft; j++)
		{
			float radianXZ1 = (float)j * PI * 2.0f / (float)spritShaft;
			float radianXZ2 = (float)(j+1) * PI * 2.0f / (float)spritShaft;
			DirectX::XMFLOAT3 workPos; 
			workPos = GetSpherePos(posBase, radianXZ1, radianY1);
			vtx[vtxNum] = { {workPos.x,workPos.y,workPos.z } ,{0.0f, 0.0f} };//左上
			vtxNum++;
			workPos = GetSpherePos(posBase, radianXZ2, radianY1);
			vtx[vtxNum] = { {workPos.x,workPos.y,workPos.z } ,{1.0f,0.0f} };//右上
			vtxNum++;
			workPos = GetSpherePos(posBase, radianXZ1, radianY2);
			vtx[vtxNum] = { {workPos.x,workPos.y,workPos.z } ,{0.0f,1.0f} };//左下
			vtxNum++;
			workPos = GetSpherePos(posBase, radianXZ2, radianY2);
			vtx[vtxNum] = { {workPos.x,workPos.y,workPos.z } ,{1.0f,1.0f} };//右下
			vtxNum++;

		}
	}

	for (int i = 0; i < (spritHeight+1)*spritShaft; i++)
	{

		int first = i * 6;
		int firstVtxNum = i * 4;
		
		idx[first + 0] = firstVtxNum;
		idx[first + 1] = firstVtxNum + 1;
		idx[first + 2] = firstVtxNum + 2;

		idx[first + 3] = firstVtxNum + 2;
		idx[first + 4] = firstVtxNum + 1;
		idx[first + 5] = firstVtxNum + 3;


	}
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = vtxNum;
	desc.vtxSize = sizeof(GeometoryVertex);
	desc.pIdx = idx;
	desc.idxCount = idxNum;
	desc.idxSize = sizeof(int);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	g_pGeometorySphere = new MeshBuffer(desc);
}
void CreateGeometoryCylinder()//2
{
	
	const int num = 6;
		float radius;
		radius = 0.5f;

		GeometoryVertex vtx[4 * num+2] = {};
		int idx[12 * num] = {};
		//上の中心
		vtx[0] = { {0.0f,0.5f,0.0f,},{0.5,1.0f} };


		//下の中心
		vtx[1] = { {0.0f,-0.5f,0.0f,},{0.5,1.0f} };
	for (int i = 0; i < num; i++)
	{
		int first = i * 4+2;
		
		//側面
		vtx[first] = { {radius * -sin( i * 3.14f * 2.0f / num), 0.5f,
			radius * cos(i * 3.14f * 2.0f / num)},{0.0f,0.0f} };//左上
		vtx[first +1] = { {radius * -sin((i + 1) * 3.14f * 2.0f / num), 0.5f,
			radius * cos((i + 1) * 3.14f * 2.0f / num)},{1.0f,0.0f} };//右上
		vtx[first +2] = { {radius * -sin(i * 3.14f * 2.0f / num), -0.5f,
			radius *  cos(i * 3.14f * 2.0f / num)},{0.0f,1.0f} };//左下
		vtx[first +3] = { {radius * -sin((i + 1) * 3.14f * 2.0f / num), -0.5f,
			radius * cos((i + 1) * 3.14f * 2.0f / num)},{1.0f,1.0f} };//右下

		
	}

	for (int i = 0; i < num; i++)
	{

		int first = i * 12;
		int firstVtxNum = i * 4+2;
		//側面
		idx[first + 0] = firstVtxNum;
		idx[first + 1] = firstVtxNum + 1;
		idx[first + 2] = firstVtxNum + 2;

		idx[first + 3] = firstVtxNum + 2;
		idx[first + 4] = firstVtxNum + 1;
		idx[first + 5] = firstVtxNum + 3;

		//上
		idx[first + 6] = firstVtxNum + 1;
		idx[first + 7] = firstVtxNum;
		idx[first + 8] = 0;

		//下
		idx[first + 9] = firstVtxNum + 2;
		idx[first + 10] = firstVtxNum + 3;
		idx[first + 11] = 1;

	}
	
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = 4 * num+2;
	desc.vtxSize = sizeof(GeometoryVertex);
	desc.pIdx = idx;
	desc.idxCount = 12 * num;
	desc.idxSize = sizeof(int);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	g_pGeometoryCylinder = new MeshBuffer(desc);
	
	
}
void CreateGeometoryCone()//3
{
	const int num = 10;
	const int vtxNum = 2 * num + 2;
	const int idxNum = 6 * num;
	float z;
	z = 0.5f;
	int i = 1;

	GeometoryVertex vtx[vtxNum] = {};
	int idx[idxNum] = {};
	//上の中心
	vtx[0] = { {0.0f,0.5f,0.0f,},{0.0,0.5f} };
	//下の中心
	vtx[1] = { {0.0f,-0.5f,0.0f,},{0.0,0.5f} };
	for (int i = 0; i < num; i++)
	{
		int first = i * 2+2;

		//側面
		//vtx[first] = { {radius * -sin(i * 3.14f * 2.0f / num), 0.5f,
		//	radius * cos(i * 3.14f * 2.0f / num)},{0.0f,0.0f} };//左上
		//vtx[first + 1] = { {radius * -sin((i + 1) * 3.14f * 2.0f / num), 0.5f,
		//	radius * cos((i + 1) * 3.14f * 2.0f / num)},{1.0f,0.0f} };//右上
		vtx[first] = { {z * -sin(i * 3.14f * 2.0f / num), -0.5f,
			z *  cos(i * 3.14f * 2.0f / num)},{0.0f,1.0f} };//左下
		vtx[first + 1] = { {z * -sin((i + 1) * 3.14f * 2.0f / num), -0.5f,
			z * cos((i + 1) * 3.14f * 2.0f / num)},{1.0f,1.0f} };//右下




	}

	for (int i = 0; i < num; i++)
	{

		int first = i * 6;
		int firstVtxNum = i * 2+2;
		//側面
		idx[first + 0] = 0;
		idx[first + 2] = firstVtxNum + 0;
		idx[first + 1] = firstVtxNum + 1;


		//下
		idx[first + 3] = 1;
		idx[first + 4] = firstVtxNum + 0;
		idx[first + 5] = firstVtxNum + 1;

	}

	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = vtxNum;
	desc.vtxSize = sizeof(GeometoryVertex);
	desc.pIdx = idx;
	desc.idxCount = idxNum;
	desc.idxSize = sizeof(int);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	g_pGeometoryCone = new MeshBuffer(desc);

}
void CreateGeometoryArrow()//5
{
}
void CreateGeometoryCapsule()//5
{
}

void CreateGeometoryShader()
{
	const char* GeometoryVS = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 wPos : TEXCOORD1;
};
cbuffer WVP : register(b0) {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);
	vout.wPos = vout.pos;
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.uv = vin.uv;
	return vout;
})EOT";
	const char* GeometoryPS = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 wPos : TEXCOORD1;	
};
float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(1,1,1,1);
	
	float2 mGrid = floor(abs(pin.uv) * 2.0f);
	float2 sGrid = floor(abs(pin.uv) * 8.0f);

	float mid = fmod(mGrid.x + mGrid.y, 2.0f);
	float small = fmod(sGrid.x + sGrid.y, 2.0f);

	color.rgb = ((mid * 0.1f) * small + 0.45f) + (1 - small) * 0.05f;
	return color;
})EOT";

	g_pGeometoryVS = new VertexShader();
	_ASSERT_EXPR(SUCCEEDED(g_pGeometoryVS->Compile(GeometoryVS)),
		L"create failed geometory vertex shader.");
	g_pGeometoryPS = new PixelShader();
	_ASSERT_EXPR(SUCCEEDED(g_pGeometoryPS->Compile(GeometoryPS)),
		L"create failed geometory pixel shader.");
}
void CreateGeometoryConstantBuffer()
{
	g_pGeometoryWVP = new ConstantBuffer();
	g_pGeometoryWVP->Create(sizeof(g_geometoryMat));

	g_geometoryTransform[0] = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_geometoryTransform[1] = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_geometoryTransform[2] = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);

	/*SetGeometoryVPMatrix(
		DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(3, 3, -3, 1), DirectX::XMVectorSet(0, 0, 0, 1), DirectX::XMVectorSet(0, 1, 0, 1)),
		DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60.f), 16.f / 9.f, 0.1f, 100.0f)
	);*/
	DirectX::XMStoreFloat4x4(&g_geometoryMat[0], DirectX::XMMatrixIdentity());
	g_pGeometoryWVP->Write(g_geometoryMat);
}
void UpdateGeometoryMatrix()
{
	//SetGeometoryRotation(0.0f, g_geometoryTransform[1].y + 0.01f, 0.0f);
	//SetGeometoryRotation(0.0f, g_geometoryTransform[1].y + 0.01f, 0.0f);

	//========
	//座標変換
	//========
	//移動　[0]に格納
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(g_geometoryTransform[0].x,
		g_geometoryTransform[0].y, g_geometoryTransform[0].z );

	//回転　[1]に格納
	//X回転
	DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(g_geometoryTransform[1].x);
	//Y回転
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(g_geometoryTransform[1].y);
	//Z回転
	DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(g_geometoryTransform[1].z);
	//拡大縮小　[2]に格納
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(g_geometoryTransform[2].x,
		g_geometoryTransform[2].y, g_geometoryTransform[2].z);
	DirectX::XMMATRIX mat = S * Rz * Ry * Rx * T;
	//転置行列へ変換
	mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMStoreFloat4x4(&g_geometoryMat[0], mat);
	g_pGeometoryWVP->Write(g_geometoryMat);
}