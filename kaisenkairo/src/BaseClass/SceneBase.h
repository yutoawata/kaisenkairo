#pragma once
#include "..\Text\GameText.h"

//シーンの基底クラス
class SceneBase {
public:
	//ゲームの状態
	enum class Type {
		NONE,
		TITLE,
		PLAY,
		CLEAR,
		GAMEOVER,
	};
protected:
	//メンバ変数
	GameText* text = nullptr;	//テキスト表示クラス
	Type next_type = Type::NONE;//遷移先のシーンの種類
	int font_size = 0;			//フォントサイズ
	float timer = 0;			//経過時間
	bool is_pause = false;		//ゲーム停止フラグ
	bool is_next = false;		//シーン遷移フラグ

public:
	//コンストラクタ
	SceneBase(int setFontSize) {
		font_size = setFontSize;
		SetFontSize(font_size);
	}

	//デストラクタ
	virtual ~SceneBase() {
		delete text;
	}

	//アクセサ
	//遷移先のシーンの種類を返す
	inline Type getNextType() { return next_type; }
	//遷移フラグを返す
	inline bool getIsNext() { return is_next; }	

	//メンバ関数
	virtual void Update() = 0;	//更新処理
	virtual void Draw() = 0;	//描画処理
};