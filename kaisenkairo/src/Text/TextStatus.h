#pragma once
#include "..\Color\Color.h"
#include <string>

//テキスト情報クラス
class TextStatus {
private:
	//メンバ変数
	std::string text;			//テキストの文字列
	int color = Color::WHITE;	//文字の色
public:
	//コンストラクタ
	TextStatus(std::string setText, int setColor);

	//アクセサ
	inline std::string getText() { return text; }//文字列を返す
	inline const char* getCharText() { return text.c_str(); }//文字列をconst char*型にキャストして返す
	inline int getColor() { return color; }	//文字列の色を返す
};