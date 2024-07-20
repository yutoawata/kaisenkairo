#pragma once
#include "..\BaseClass\SceneBase.h"

class ResultScene : public SceneBase {
private:
	static const std::vector<std::string> clear_texts;
	static const std::vector<std::string> gameover_texts;
public:
	ResultScene(int fontSize = 120);

	void Update() override;
	void Draw() override;
};

class ClearScene : public SceneBase {
private:
	//メンバ変数
	std::vector<std::string> texts = {//クリアテキスト
		"        通信完了",
		"	目の端末にたどり着いた",
		"エンターキーでタイトルに戻る"
	};
public:
	//コンストラクタ
	ClearScene(int fontSize = 120)
		:SceneBase(fontSize) {
		next_type = Type::TITLE;
		text = new GameText(Vector(200, 400), texts, Color::WHITE, font_size);
	}

	//メンバ関数
	//更新処理
	void Update() override;
	//描画処理
	void Draw() override;
};

class GameOverScene : public SceneBase {
private:
	//メンバ変数
	std::vector<std::string> texts = {//クリアテキスト
		"        通信失敗",
		"	　	電波が途切れた",
		"エンターキーでタイトルに戻る"
	};
public:
	//コンストラクタ
	GameOverScene(int fontSize = 120)
		:SceneBase(fontSize) {
		next_type = Type::TITLE;
		text = new GameText(Vector(200, 400), texts, Color::WHITE, font_size);
	}

	//メンバ関数
	//更新処理
	void Update() override;
	//描画処理
	void Draw() override;

};