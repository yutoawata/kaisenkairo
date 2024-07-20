#pragma once
#include "DxLib.h"
#include "..\Collider\CircleCollider.h"
#include "..\Collider\LineCollider.h"

//当たり判定処理クラス
class ColliderManager {
private:
	//メンバ変数
	std::unordered_map<ObjectType, LineCollider*> line_colliders;//線分の当たり判定情報配列
	std::vector<CircleCollider*> circle_colliders;	//円の当たり判定情報配列
	CircleCollider* player_collider = nullptr;		//プレイヤーの当たり判定情報
	//コンストラクタ
	ColliderManager();
	ColliderManager(const ColliderManager&) = delete;
public:
	//デストラクタ
	~ColliderManager();

	//メンバ関数
	//他ファイルでの呼び出し用の関数
	static ColliderManager& Instance();
	//各コライダの更新処理
	void Update();	
	//オブジェクトの円コライダを配列に保存
	void AddList(CircleCollider* collider);
	//オブジェクトの線コライダを配列に保存
	void AddList(LineCollider* collider);
	//コライダの登録情報をクリア
	void ClearColliders();

private:
	//円と円の衝突フラグのチェック
	void UpdateFlag(CircleCollider* collider01, CircleCollider* collider02);
	//円と線の衝突フラグのチェック
	void UpdateFlag(CircleCollider* cCollider, LineCollider* lCollider);
	//円と円の当たり判定処理
	bool CheckCollision(CircleCollider& collider01, CircleCollider& collider02) const;
	//円と線の当たり判定
	bool CheckCollision(CircleCollider& circleCollider, LineCollider& lineCollider) const;
};