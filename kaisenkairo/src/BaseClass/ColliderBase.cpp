#include "ColliderBase.h"

//コンストラクタ
ColliderBase::ColliderBase(Vector setPosition, ObjectType setType) {
	position = setPosition;
	type = setType;
}

//デストラクタ
ColliderBase::~ColliderBase() {}

//円の当たり判定の結果上伸処理
void ColliderBase::UpdateFlag(const ColliderBase& other) {
	others.emplace_back(other);	//当たった相手のコライダーを保存
}

//リセット処理
void ColliderBase::Reset() {
	others.clear();//Collider情報をリセット
}
