#pragma once
#include <string>
#include "DxLib.h"
#include "..\Color\Color.h"
#include "..\Math\Vector.h"

//枠線クラス
class Frame {
private:
	//メンバ変数
	std::string name = "";			//枠線の名前
	Vector position = Vector(0, 0);	//枠線の左上の座標
	int width = 0;	//横幅
	int height = 0;	//縦幅
public:
	//コンストラクタ
	Frame(Vector setPosition, int setWidth, int setHeight, std::string setName = "");

	//メンバ関数
	//描画処理
	void Draw();
};