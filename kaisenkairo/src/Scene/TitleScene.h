#pragma once
#include "..\BaseClass\SceneBase.h"

//タイトルシーンクラス
class TitleScene : public SceneBase {
private:
	//メンバ変数
	std::vector<std::string> texts = {//タイトルテキスト
		"         回線回廊",
		"正しい道を進み、ループから抜け出せ",
		"	Input Space to Start Game"
	};
public:
	//コンストラクタ
	TitleScene(int fontSize = 100);

	//メンバ関数
	void Update() override;	//更新処理
	void Draw() override;	//描画処理
};