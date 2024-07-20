#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include"DxLib.h"

class Vector {
private:
	//メンバ変数
	float x = 0.0f;//座標のX成分
	float y = 0.0f;//座標のY成分

public:
	//コンストラクタ
	Vector() {}
	Vector(int setX, int setY);
	Vector(float setX, float setY);

	//演算子オーバーロード
	Vector operator +(const Vector& other);	//Vectorクラス同士の加算を追加4
	Vector operator -(const Vector& other);	//Vectorクラス同士の減算を追加
	Vector operator *(float value);			//各要素への乗算を追加
	Vector operator /(float value);			//各要素への除算を追加
	Vector& operator +=(const Vector& other);
	Vector& operator -=(const Vector& other);
	bool operator ==(const Vector& other);	//Vectorクラス同士の比較を追加
	operator VECTOR();//DXライブラリ対応のベクトルへのキャストを追加

	//アクセサ
	//DxLibの描画関数では座標成分がint型対応の為キャストして渡す
	inline int getPosX() { return static_cast<int>(x); }
	inline int getPosY() { return static_cast<int>(y); }
	//X成分を返す
	inline float getX() { return x; }
	//Y成分を返す
	inline float getY() { return y; }

	//メンバ関数
	//引数のベクトルの単位ベクトルを返す
	static Vector Normalize(Vector mine);
	//ベクトルの長さを返す
	float getSize() { return (float)sqrt(x * x + y * y); }
	//ベクトルのNULLフラグを返す
	bool IsZero() { return x == 0 && y == 0; }
};