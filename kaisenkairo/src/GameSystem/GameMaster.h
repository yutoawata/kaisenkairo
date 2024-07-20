#pragma once
#include "DxLib.h"
#include "..\Color\Color.h"
#include "..\GameSystem\FPSController.h"
#include "..\Scene\TitleScene.h"
#include "..\Scene\PlayScene.h"
#include "..\Scene\ResultScene.h"

//ゲームのメインループを行うクラス
class GameMaster {
private:
	//メンバ定数
	const int SCREEN_WIDTH = 1920;	//ゲームウィンドウの横幅
	const int SCREEN_HEIGHT = 1080;	//ゲームウィンドウの縦幅
	const int SCREEN_COLOR = 32;	//ゲームウィンドウのカラービット数

	//メンバ変数
	SceneBase* current_scene = nullptr;//各シーンごとの処理をするクラス
	bool is_init = false;
public:
	//コンストラクタ
	GameMaster();

	//デストラクタ
	~GameMaster();

	//メンバ関数
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//メインループ処理
	void Run();
	//シーン遷移処理
	void ChangeScene(SceneBase::Type nextStatus);
};