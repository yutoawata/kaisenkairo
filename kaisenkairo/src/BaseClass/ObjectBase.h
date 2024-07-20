#pragma once
#include <iostream>
#include "DxLib.h"
#include "..\Color\Color.h"
#include "..\Math\Vector.h"

//移動を前提としたオブジェクトの基底クラス
class ObjectBase {
protected:
	//メンバ変数
	Vector position;//中心座標
	int color;		//描画時の色

public:
	//コンストラクタ
	ObjectBase(Vector setPos, int setColor = Color::WHITE) {
		position = setPos;
		color = setColor;
	}

	//デストラクタ
	virtual ~ObjectBase() {}

	//アクセサ
	//描画時の色を返す
	inline int getColor() { return color; }
	
	//メンバ関数
	virtual void Prepare() = 0;	//更新前処理
	virtual void Update() = 0;	//更新処理
	virtual void Draw() = 0;	//描画処理
};