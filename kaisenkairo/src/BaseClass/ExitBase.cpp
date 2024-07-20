#include "ExitBase.h"

//コンストラクタ
ExitBase::ExitBase(int exitMapId, int setColor) {
	next_map_id = exitMapId;
	color = setColor;
}

//デストラクタ
ExitBase::~ExitBase() {
	delete collider;
}

//更新処理
void ExitBase::Prepare() {
	collider->Reset();//当たり判定情報をリセット
}

//描画処理
void ExitBase::Draw() {
	//コの字型で描画
	for (int i = 0; i < lines.size(); i++) {
		DrawLine(lines[i].getBegin().getPosX(), lines[i].getBegin().getPosY(),	//始点座標
				 lines[i].getEnd().getPosX(),	lines[i].getEnd().getPosY(),	//終点座標
				 Color::WHITE//線分を表示する際の色
		);
	}
}

//プレイヤーが入ってきたかの判定処理
bool ExitBase::CheckEnter() {
	for (ColliderBase& other : collider->getOthers()) {
		//プレイヤーと衝突しているなら
		if (other.getType() == ObjectType::PLAYER) {
			return true;
		}
	}
	return false;
}

ObjectType ExitBase::GetEnterType(ObjectType exitType) {
	switch (exitType) {
	case ObjectType::UP_EXIT:
		return ObjectType::DOWN_EXIT;
		break;
	case ObjectType::DOWN_EXIT:
		return ObjectType::UP_EXIT;
		break;
	case ObjectType::RIGHT_EXIT:
		return ObjectType::LEFT_EXIT;
		break;
	case ObjectType::LEFT_EXIT:
		return ObjectType::RIGHT_EXIT;
		break;
	default:
		throw std::invalid_argument("無効な ObjectType が渡されました"); // 例外をスロー;
		break;
	}
}