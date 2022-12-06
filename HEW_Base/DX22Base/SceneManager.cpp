#include "SceneManager.h"

void CSceneManager::Init()
{
	//�N�����̃V�[����ݒ�
	m_CurrentScene = m_NextScene = SCENE_TITLE;

	//���݂̃V�[���ɂ���ď����𕪊�
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
	//���݂̃V�[���ɂ���ď����𕪊�
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
	//���݂̃V�[���ɂ���ď����𕪊�
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
	//���݂̃V�[���ɂ���ď����𕪊�
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
	//���݂̃V�[���̏I��
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

	//�V�[���̍X�V
	m_CurrentScene = m_NextScene;

	//���̃V�[���̏�����
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
