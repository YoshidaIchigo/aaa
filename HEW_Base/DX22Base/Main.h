#ifndef __MAIN_H__
#define __MAIN_H__

#include "SceneManager.h"

//--- プロトタイプ宣言
unsigned int GetAppWidth();
unsigned int GetAppHeight();

void Init();
void Uninit();
void Update(float deltaTime);
void Draw();

CSceneManager* GetSceneManager();

#endif // __MAIN_H__