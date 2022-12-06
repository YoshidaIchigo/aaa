#include "Title.h"
#include "Main.h"
#include "Input.h"


CTitle::CTitle()
{
}

CTitle::~CTitle()
{
}

void CTitle::Update()
{
	if(IsKeyPress(VK_F1))
	{
		GetSceneManager()->StartSceneChange(SCENE_GAME);
	}
}

void CTitle::Draw()
{
	
}
