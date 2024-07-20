#include "CircleCollider.h"

//コンストラクタ
CircleCollider::CircleCollider(Vector setPos, int setRad, ObjectType setType)
	: ColliderBase(setPos, setType) {
	radius = setRad;
}

//座標の更新処理
void CircleCollider::UpdatePosition(Vector newPos) {
	position = newPos;
}