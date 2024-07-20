#pragma once
#include "DxLib.h"
#include "..\ManagerClass\ColliderManager.h"
#include "..\BaseClass\ObjectBase.h"

//敵対オブジェクトクラス
class Enemy : public ObjectBase {
private:
	//メンバ変数
	CircleCollider* collider = nullptr;	//当たり判定
	Vector home_pos = Vector(0, 0);		//座標
	int radius = 15;	//描画時の円の半径
	float speed = 0.5f;	//移動速度

public:
	//コンストラクタ
	Enemy(Vector setPos);

	//デストラクタ
	~Enemy();

	//メンバ関数
	void Prepare() override;//更新前処理
	void Update() override;	//更新処理
	void Draw() override;	//描画処理
private:
	void Move(Vector playerPos);	//移動処理
};
