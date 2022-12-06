#include "SceneManager.h"

void CSceneManager::Init()
{
	//起動時のシーンを設定
	m_CurrentScene = m_NextScene = SCENE_TITLE;

	//現在のシーンによって処理を分岐
	switch (m_CurrentScene)
	{
	case (SCENE_TITLE):
		m_pTitle = new CTitle();
		break;
	case (SCENE_GAME):
		m_pGame = new Game3D();
		break;
	case (SCENE_RESULT):
		m_pResult = new CResult();
		break;
	}
}

void CSceneManager::Uninit()
{
	//現在のシーンによって処理を分岐
	switch (m_CurrentScene)
	{
	case (SCENE_TITLE):
		delete m_pTitle;
		break;
	case (SCENE_GAME):
		delete m_pGame;
		break;
	case (SCENE_RESULT):
		delete m_pResult;
		break;
	}
}

void CSceneManager::Update()
{
	//現在のシーンによって処理を分岐
	switch (m_CurrentScene)
	{
	case (SCENE_TITLE):
		m_pTitle->Update();
		break;
	case (SCENE_GAME):
		m_pGame->Update();
		break;
	case (SCENE_RESULT):
		m_pResult->Update();
		break;
	}
}

void CSceneManager::Draw()
{
	//現在のシーンによって処理を分岐
	switch (m_CurrentScene)
	{
	case (SCENE_TITLE):
		m_pTitle->Draw();
		break;
	case (SCENE_GAME):
		m_pGame->Draw();
		break;
	case (SCENE_RESULT):
		m_pResult->Draw();
		break;
	}
}

E_SCENE_TYPE CSceneManager::GetCurrentScene()
{
	return m_CurrentScene;
}

void CSceneManager::StartSceneChange(E_SCENE_TYPE next)
{
	m_NextScene = next;

	SetSceneChange();
}

void CSceneManager::SetSceneChange()
{
	//現在のシーンの終了
	switch (m_CurrentScene)
	{
	case (SCENE_TITLE):
		delete m_pTitle;
		break;
	case (SCENE_GAME):
		delete m_pGame;
		break;
	case (SCENE_RESULT):
		delete m_pResult;
		break;
	}

	//シーンの更新
	m_CurrentScene = m_NextScene;

	//次のシーンの初期化
	switch (m_CurrentScene)
	{
	case (SCENE_TITLE):
		m_pTitle = new CTitle();
		break;
	case (SCENE_GAME):
		m_pGame = new Game3D();
		break;
	case (SCENE_RESULT):
		m_pResult = new CResult();
		break;
	}
}

Game3D * CSceneManager::GetGame()
{
	return m_pGame;
}
