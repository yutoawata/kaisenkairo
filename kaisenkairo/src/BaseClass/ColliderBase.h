#pragma once
#include "..\Math\Methods.h"
#include "..\Math\Vector.h"
#include <vector>

//オブジェクトの種類
enum class ObjectType {
	PLAYER,		//プレイヤー
	ENEMY,		//エネミー
	WALL,		//壁
	UP_EXIT,	//上出口
	DOWN_EXIT,	//下出口
	RIGHT_EXIT,	//右出口
	LEFT_EXIT,	//左出口
};

//当たり判定の基本情報クラス
class ColliderBase {
protected:
	//メンバ変数
	std::vector<ColliderBase> others;	//当たった相手
	Vector position = Vector(0, 0);		//オブジェクトの座標
	ObjectType type;	//自身の種類
	
public:
	//コンストラクタ
	ColliderBase(Vector setPosition, ObjectType setType);

	//デストラクタ
	virtual ~ColliderBase();

	//アクセサ
	//当たった相手の当たり判定情報を返す
	inline std::vector<ColliderBase>& getOthers() { return others; }
	//コライダーの座標を返す
	inline Vector getPosition() { return position; }
	//自身の種類のゲッター
	inline ObjectType getType() { return type; }
	
	//メンバ関数
	//相手の種類・衝突フラグのリセット
	void Reset();
	//衝突した相手の種類を保存・フラグをON(円の当たり判定)
	void UpdateFlag(const ColliderBase& other);
};