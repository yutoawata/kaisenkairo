#include "PlayScene.h"

//コンストラクタ
PlayScene::PlayScene(int fontSize)
	:SceneBase(fontSize) {
	font_size = fontSize;
	next_type = Type::CLEAR;
	text = new GameText(Vector(960, 840), texts, Color::YELLOW, font_size);
	MapManager::Instance().SetUpMap();
	ObjectManager::Instance().EntryPlayer(font_size);
	ObjectManager::Instance().EntryEnemy();
}

//デストラクタ
PlayScene::~PlayScene() {
	delete view_frame;
	delete text_frame_01;
	delete text_frame_02;
}

//更新処理
void PlayScene::Update() {
	//各管理クラスの更新前処理を行う
	ObjectManager::Instance().Prepare();
	MapManager::Instance().Prepare();

	//各管理クラスの更新処理を行う
	ColliderManager::Instance().Update();
	MapManager::Instance().Update();
	ObjectManager::Instance().Update();

	CheckResult();
}

//描画処理
void PlayScene::Draw() {
	//マップ管理クラスの描画処理を行う
	MapManager::Instance().Draw();
	//カットイン状態でないなら
	if (!MapManager::Instance().getIsCutin()) {
		//オブジェクト管理クラスの描画処理を行う
		ObjectManager::Instance().Draw();
		text->Draw();
		view_frame->Draw();
		text_frame_01->Draw();
		text_frame_02->Draw();
	}
}

//ゲームプレイ結果のチェック
void PlayScene::CheckResult() {
	//ゲームのる例結果を取得
	ObjectManager::ResultStatus result = ObjectManager::Instance().CheckResult(MapManager::Instance().getIntStageNum());
	switch (result) {
	case ObjectManager::ResultStatus::PLAY://ゲーム中なら
		//何もせずに処理を抜ける
		break;
	case ObjectManager::ResultStatus::CLEAR://ゲームクリアなら
		next_type = Type::CLEAR;//遷移後のシーンの種類にクリアを代入
		is_next = true;			//遷移フラグをtrueにする
		break;
	case ObjectManager::ResultStatus::GAME_OVER://ゲームオーバーなら
		next_type = Type::GAMEOVER;	//遷移先のシーンの種類にゲームオーバーを代入
		is_next = true;				//遷移フラグをtrueにする
		break;
	}
}