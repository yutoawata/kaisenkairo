#include "TitleScene.h"

//コンストラクタ
TitleScene::TitleScene(int fontSize)
	:SceneBase(fontSize) {
	next_type = Type::PLAY;
	text = new GameText(Vector(200, 400), texts, Color::WHITE, font_size);
}

//更新処理
void TitleScene::Update() {
	if (CheckHitKey(KEY_INPUT_SPACE))
		is_next = true;//遷移フラグをtrueにする
}

//描画処理
void TitleScene::Draw() {
	text->Draw();//テキスト描画処理
}