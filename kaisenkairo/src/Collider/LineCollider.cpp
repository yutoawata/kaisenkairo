#include "LineCollider.h"

//コンストラクタ
LineCollider::LineCollider(std::vector<Ray2> setLines, Vector setPos, ObjectType setType)
	: ColliderBase(setPos, setType) {
	lines = setLines;
}

LineCollider::~LineCollider() {}

//座標の更新処理
void LineCollider::UpdateLines(std::vector<Ray2> newLines) {
	lines = newLines;
}