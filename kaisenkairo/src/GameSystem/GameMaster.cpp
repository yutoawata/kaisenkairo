#include "DxLib.h"
#include "GameMaster.h"

//コンストラクタ
GameMaster::GameMaster() {
	//ゲームの解像度設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR);
	//ゲームをフルスクリーンに設定
	ChangeWindowMode(FALSE);
	//ライブラリ開始
	is_init = static_cast<bool>(DxLib_Init());
	//マウスカーソルの表示をOFF
	SetMouseDispFlag(FALSE);
	//描画領域の設定
	SetDrawScreen(DX_SCREEN_BACK);
	//ゲーム開始時のシーンを設定
	ChangeScene(SceneBase::Type::TITLE);
}

//デストラクタ
GameMaster::~GameMaster() {
	delete current_scene;
	DxLib_End();
}

//シーン遷移処理
void GameMaster::ChangeScene(SceneBase::Type nextScene) {
	
	delete current_scene;//遷移前のシーンを削除

	switch (nextScene) {
	case SceneBase::Type::TITLE:
		current_scene = new TitleScene();//タイトルに遷移
		break;
	case SceneBase::Type::PLAY:
		current_scene = new PlayScene();//ゲームプレイシーンに遷移
		break;
	case SceneBase::Type::CLEAR:
		current_scene = new ClearScene();//クリアシーンクラスに遷移
		break;
	case SceneBase::Type::GAMEOVER:
		current_scene = new GameOverScene();//ゲームオーバーシーンに遷移
		break;
	default:
		is_init = false;//誤動作の為ゲームを終了
		break;
	}
}

void GameMaster::Update() {
	//現在のシーンがない　または　遷移フラグがtureなら
	if (current_scene == nullptr || current_scene->getIsNext())
		ChangeScene(current_scene->getNextType());//遷移処理を実行

	current_scene->Update();
	//マウスカーソルの座標を中心に戻す
	SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

//画面の枠を描画
void GameMaster::Draw() {
	//現在のシーンの描画処理
	current_scene->Draw();
}

//ゲームループ処理
void GameMaster::Run() {
	while (!ProcessMessage() && !is_init) {

		ClearDrawScreen();
		Update();
		Draw();

		//Escapeキーでゲームを強制終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) 
			break;
		
		FPSController::Instance().Update();

		ScreenFlip();//フリップ関数

		FPSController::Instance().Wait();
	}
}