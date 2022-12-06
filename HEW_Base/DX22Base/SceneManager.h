#pragma once

#include "Title.h"
#include "Game3D.h"
#include "Result.h"


//�V�[���̏�Ԃ��Ǘ�����񋓑�
enum E_SCENE_TYPE
{
	SCENE_TITLE = 0, //�^�C�g��
	SCENE_GAME, //�Q�[���{��
	SCENE_RESULT, //���U���g���
	MAX_SCENE
};

//�V�[�����Ǘ�����N���X
class CSceneManager
{
public:
	void Init(); //�V�[���̏�����
	void Uninit(); //�V�[���̏I��
	void Update(); //�V�[���̍X�V
	void Draw(); //�V�[���̕`��

	E_SCENE_TYPE GetCurrentScene(); //���݂̃V�[�������擾

	void StartSceneChange(E_SCENE_TYPE next); //�V�[�����Z�b�g����
	void SetSceneChange(); //���ۂɃV�[����؂�ւ���ۂɌĂ΂��

	Game3D* GetGame();

private:
	E_SCENE_TYPE m_CurrentScene; //���݂̃V�[�����Ǘ�����ϐ�
	E_SCENE_TYPE m_NextScene; //�J�ڐ�̃V�[�����Ǘ�����ϐ�

	//�e�V�[���̃|�C���^
	CTitle* m_pTitle;
	Game3D* m_pGame;
	CResult* m_pResult;

};
