#pragma once
#include "..\BaseClass\ColliderBase.h"

//円の当たり判定コライダークラス
class CircleCollider : public ColliderBase {
private:
	//メンバ変数
	int radius = 0;//半径

public:
	//コンストラクタ
	CircleCollider(Vector setPos, int setRad, ObjectType setType);

	//アクセサ
	//中心座標を返す
	inline Vector getPosition() { return position; }
	//半径を返す
	inline int getRadius() { return radius; }

	//メンバ関数
	//座標の更新処理
	void UpdatePosition(Vector newPos);
};