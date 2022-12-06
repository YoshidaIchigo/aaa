#include "Result.h"
#include "Main.h"
#include "Input.h"

CResult::CResult()
{
}

CResult::~CResult()
{
}

void CResult::Update()
{
	if (IsKeyPress(VK_F1))
	{
		GetSceneManager()->StartSceneChange(SCENE_TITLE);
	}
}

void CResult::Draw()
{

}
