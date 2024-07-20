#include "ColliderManager.h"

ColliderManager::ColliderManager() {}

ColliderManager::~ColliderManager() {}

//保存したコライダ情報を削除
void ColliderManager::ClearColliders() {
	circle_colliders.clear();
	line_colliders.clear();
}

//他ファイルでの呼び出し用の関数
ColliderManager& ColliderManager::Instance() {
	static ColliderManager instance;
	return instance;
}

//当たり判定処理をするColliderのリストに追加
void ColliderManager::AddList(CircleCollider* collider) {
	if (collider->getType() == ObjectType::PLAYER) {
		player_collider = collider;
	}
	else {
		circle_colliders.emplace_back(collider);
	}
}

//当たり判定処理をするColliderのリストに追加
void ColliderManager::AddList(LineCollider* collider) {
	line_colliders[collider->getType()] = collider;
}

void ColliderManager::Update() {
	//線文との当たり判定
	for (auto& line_collider : line_colliders) {
		UpdateFlag(player_collider, line_collider.second);
	}
	//エネミーの当たり判定
	for (int i = 0; i < circle_colliders.size(); i++) {
		UpdateFlag(player_collider, circle_colliders[i]);
	}
}

//円と円の当たり判定情報の更新処理
void ColliderManager::UpdateFlag(CircleCollider* collider01, CircleCollider* collider02) {
	if (CheckCollision(*collider01, *collider02)) {
		//当たり判定結果を更新
		collider01->UpdateFlag(*collider02);
		collider02->UpdateFlag(*collider01);
	}
}

//円と線の当たり判定情報の更新処理
void ColliderManager::UpdateFlag(CircleCollider* cCollider, LineCollider* lCollider) {
	if (CheckCollision(*cCollider, *lCollider)) {
		//円の当たり判定結果を更新
		cCollider->UpdateFlag(*lCollider);
		//線分の当たり判定結果を更新
		lCollider->UpdateFlag(*cCollider);
	}
}

//円と円の当たり判定
bool ColliderManager::CheckCollision(CircleCollider& collider01, CircleCollider& collider02) const {
	//collider02の中心座標=>collider01の中心座標のベクトルを生成
	VECTOR distance_vec = VSub(collider01.getPosition(), collider02.getPosition());
	float distance_magnitude = VSize(distance_vec);//ベクトルの大きさから距離を求める

	//二つの円の半径の和より距離が近ければ衝突している
	if (distance_magnitude < collider01.getRadius() + collider02.getRadius())
		return true;

	return false;
}

//円と線の当たり判定
bool ColliderManager::CheckCollision(CircleCollider& circleCollider, LineCollider& lineCollider) const {

	int circle_radius = circleCollider.getRadius();//円の半径を取得
	for (int i = 0; i < lineCollider.getLines().size(); i++) {
		Ray2 line = lineCollider.getLines()[i];//線分の当たり判定情報を配列から抽出
		Vector begin_to_center = circleCollider.getPosition() - line.getBegin();//線分の始点=>円の中心のベクトルを生成
		Vector end_to_centor = circleCollider.getPosition() - line.getEnd();	//線分の終点=>円の中心のベクトルを生成
		Vector begin_to_end = line.getEnd() - line.getBegin();//線分のベクトルを生成

		Vector normal_begin_to_end = Vector::Normalize(begin_to_end);		//線分のベクトルを正規化
		Vector normal_begin_to_center = Vector::Normalize(begin_to_center);	//線分の始点=>円の中心のベクトルを正規化
		//外積計算
		float cross = normal_begin_to_end.getX() * begin_to_center.getY() - normal_begin_to_end.getY() * begin_to_center.getX();

		//絶対値として扱いたいため、負の値なら正の値として返す
		cross = cross < 0 ? -cross : cross;

		//外積の値が半径の値以上のとき、衝突してないので次のループに行く
		if (cross >= circle_radius) continue;

		float dot_01 = begin_to_center.getX() * begin_to_end.getX() + begin_to_center.getY() * begin_to_end.getY();
		float dot_02 = end_to_centor.getX() * begin_to_end.getX() + end_to_centor.getY() * begin_to_end.getY();

		//始点=>円の内積と終点=>円の内積を掛けた値が0以下のなら、衝突している
		if (dot_01 * dot_02 <= 0) return true;

		//始点=>円のベクトルの長さと終点=>円のベクトルの長さのどちらかが円の半径以上のなら
		if (VSize(begin_to_center) > circle_radius || VSize(end_to_centor) > circle_radius)
			continue;//重なっていないので次のループに行く

		return true;
	}
	return false;
}
