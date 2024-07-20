#include "ResultScene.h"

const std::vector<std::string> ResultScene::clear_texts = {
		"        通信完了",
		"	目の端末にたどり着いた",
		"エンターキーでタイトルに戻る"
};

const std::vector<std::string> ResultScene::gameover_texts = {
	"        通信失敗",
	"	　	電波が途切れた",
	"エンターキーでタイトルに戻る"
};

ResultScene::ResultScene(int fontSize)
	: SceneBase(fontSize) {
	
}

void ResultScene::Update() {
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		is_next = true;
	}
}

void ResultScene::Draw() {
	text->Draw();//テキスト描画処理
}


//更新処理
void ClearScene::Update() {
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		is_next = true;
	}
}

//描画処理
void ClearScene::Draw() {
	text->Draw();//テキスト描画処理
}
//////////////////////////////////////////////////////////////////////

//更新処理
void GameOverScene::Update() {
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		is_next = true;
	}
}

//描画処理
void GameOverScene::Draw() {
	text->Draw();//テキスト描画処理
}