#include "Enemy.h"

//コンストラクタ
Enemy::Enemy(Vector setPos)
	: ObjectBase(setPos) {
	position = setPos;
	home_pos = setPos;
	collider = new CircleCollider(position, 90, ObjectType::ENEMY);
	ColliderManager::Instance().AddList(collider);
}

//デストラクタ
Enemy::~Enemy() {
	delete collider;
}

//更新前処理
void Enemy::Prepare() {
	//コライダー情報をリセット
	collider->Reset();
}

//更新処理
void Enemy::Update() {
	//移動する目的地(初期化値:スポーン座標)
	Vector target_position = home_pos;

	for (ColliderBase other : collider->getOthers()) {
		//当たった相手の種類を取得
		ObjectType ohter_type = other.getType();

		//Playerと当たっているなら
		if (ohter_type == ObjectType::PLAYER) {
			//当たった相手の座標を目的地にする
			target_position = other.getPosition();
			break;
		}
	}
	Move(target_position);//移動処理
}

//描画処理
void Enemy::Draw() {
	//自身の座標を円で描画
	DrawCircle(position.getPosX(), position.getPosY(), radius, Color::RED, TRUE);
}

//移動処理
void Enemy::Move(Vector targetPos) {
	Vector direction = targetPos - position;	//移動方向
	float direction_size = direction.getSize();	//移動先との距離

	//処理が一回の移動分より遠ければ
	if (direction_size >= speed) {
		Vector normal_direction = Vector::Normalize(direction);
		//移動後の座標を代入
		position = position + Vector(normal_direction.getX() * speed, normal_direction.getY() * speed);
		//コライダーの座標を更新
		collider->UpdatePosition(position);
	}
}