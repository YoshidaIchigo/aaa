#pragma once

#include "Title.h"
#include "Game3D.h"
#include "Result.h"


//シーンの状態を管理する列挙体
enum E_SCENE_TYPE
{
	SCENE_TITLE = 0, //タイトル
	SCENE_GAME, //ゲーム本編
	SCENE_RESULT, //リザルト画面
	MAX_SCENE
};

//シーンを管理するクラス
class CSceneManager
{
public:
	void Init(); //シーンの初期化
	void Uninit(); //シーンの終了
	void Update(); //シーンの更新
	void Draw(); //シーンの描画

	E_SCENE_TYPE GetCurrentScene(); //現在のシーン情報を取得

	void StartSceneChange(E_SCENE_TYPE next); //シーンをセットする
	void SetSceneChange(); //実際にシーンを切り替える際に呼ばれる

	Game3D* GetGame();

private:
	E_SCENE_TYPE m_CurrentScene; //現在のシーンを管理する変数
	E_SCENE_TYPE m_NextScene; //遷移先のシーンを管理する変数

	//各シーンのポインタ
	CTitle* m_pTitle;
	Game3D* m_pGame;
	CResult* m_pResult;

};
