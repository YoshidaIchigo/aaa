#include "Main.h"
#include "DirectX.h"
#include "WinUtil.h"
#include "DirectXTex/Texture.h"
#include "Input.h"
#include "SceneManager.h"
#include "Geometory.h"

//--- 定数定義
const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;

//-- グローバル変数
CSceneManager* g_pSceneManager;

unsigned int GetAppWidth()
{
	return SCREEN_WIDTH;
}
unsigned int GetAppHeight()
{
	return SCREEN_HEIGHT;
}

void Init()
{
	if (FAILED(InitDX(GetHWND(), SCREEN_WIDTH, SCREEN_HEIGHT, false)))
	{
		Error("directx initialize failed.");
	}
	if (FAILED(InitTexture(GetDevice())))
	{
		Error("texture initialize failed.");
	}
	if (FAILED(InitInput()))
	{
		Error("input initialize failed.");
	}
	if (FAILED(InitGeometory()))
	{
		Error("geometory initialize failed.");
	}
	//起動時のシーンをここでセット
	g_pSceneManager = new CSceneManager();
	g_pSceneManager->Init();
}
void Uninit()
{
	delete g_pSceneManager;
	UninitGeometory();
	UninitInput();
	UninitTexture();
	UninitDX();
}
void Update(float deltaTime)
{
	UpdateInput();
	g_pSceneManager->Update();
}
void Draw()
{
	BeginDrawDX();
	g_pSceneManager->Draw();
	EndDrawDX();
}

CSceneManager* GetSceneManager()
{
	return g_pSceneManager;
}
