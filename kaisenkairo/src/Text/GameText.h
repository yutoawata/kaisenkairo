#pragma once
#include <vector>
#include <functional>
#include "DxLib.h"
#include "..\Math\Vector.h"
#include "TextStatus.h"

//テキスト描画クラス
class GameText {
private:
	//メンバ変数
	static const int LOG_LINE_VALUE = 5;//描画できる文字列の最大値
	using add_text_function = std::function<void(std::vector<TextStatus>&)> ;//型名が長くなるので型名を宣言
	add_text_function add_function = nullptr;//文字列を追加する関数のポインタ
	std::vector<TextStatus> texts;	//文字列情報のポインタ
	Vector position = Vector(0, 0);	//描画する座標
	int font_size = 0;//文字のサイズ

public:
	//コンストラクタ
	GameText(Vector setPosition, std::vector<std::string> setTexts, int setColor, int fontSize, add_text_function set_function = nullptr);

	//デストラクタ
	~GameText();

	//メンバ関数
	//更新処理
	void Update();
	//描画処理
	void Draw();
};
