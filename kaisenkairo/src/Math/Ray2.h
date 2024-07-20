#pragma once
#include "..\Color\Color.h"
#include "Vector.h"

//線分クラス
class Ray2 {
private:
	//メンバ変数
	Vector begin = Vector(0, 0);//始点座標
	Vector end = Vector(0, 0);	//終点座標
	int color = Color::WHITE;	//線分の色

public:
	//コンストラクタ
	Ray2();
	Ray2(Vector setBegin, Vector setEnd, int setColor = Color::WHITE);

	//アクセサ
	//始点を渡す
	inline Vector getBegin() { return begin; }
	//終点を渡す
	inline Vector getEnd() { return end; }
	//線分の色を渡す
	inline int getColor() { return color; }
};