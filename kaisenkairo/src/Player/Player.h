#pragma once
#include "DxLib.h"
#include "..\BaseClass\ObjectBase.h"
#include "..\ManagerClass\ColliderManager.h"
#include "..\Text\GameText.h"
#include "..\Color\Color.h"
#include "..\Math\Methods.h"
#include "View.h"

class Player : public ObjectBase {
private:
	//メンバ定数
	const int RADIUS = 20;			//描画時の円の半径
	const int MAX_HIT_POINT = 100;	//hit_pointの上限
	const int HALF_HIT_POINT = 50;	//hit_pointの半分
	const int MAX_LOG_LINE = 5;
	const float ROTATE_SPEED = 30.0f;	//視点の回転速度
	const float MOVE_SPEED = 1.5f;		//移動速度
	const float DAMAGE_INTERVAL = 0.2f;	//ダメージを受ける感覚
	const float ADD_LOG_INTERVAL = 2.0f;//ログを追加する間隔

	//メンバ変数
	std::vector<int> route;				//移動したマップの順序を保存する配列
	std::vector<std::string> text;		//テキスト表示クラスで表示する文字列
	CircleCollider* collider = nullptr;	//当たり判定(円)
	GameText* log = nullptr;	//テキスト表示クラス
	View* view = nullptr;		//視界描画クラス
	int hit_point = 100;		//プレイヤーのHP
	float angle = 0.0f;			//向いている角度
	float timer = 0.0f;			//経過時間計測変数
	float move_timer = 0.0f;	//移動時間
	bool is_move = false;		//移動しているかのフラグ
	bool can_add_log = false;	//ログを追加できるかのフラグ
	bool is_damage = false;		//ダメージを受けているかのフラグ
	
public:
	//コンストラクタ
	Player(Vector setPos, int setAngle, int fontSize);
	//デストラクタ
	~Player();

	//アクセサ
	inline CircleCollider GetCollider() { return *collider; }	//当たり判定の情報を渡す
	inline Vector getPosition() { return position; }//プレイヤーの座標を渡す
	inline int gethitPoint() { return hit_point; }	//HitPointを返す
	inline bool getIsMove() { return is_move; }		//移動距離を渡す
	inline float getAngle() {return angle;}			//向いている角度

	//メンバ関数
	//更新前処理
	void Prepare() override;
	//更新処理
	void Update() override;
	//描画処理
	void Draw() override;
	//ゴールに着いたかの判定処理
	bool CheckGoal(std::vector<int>stageId);
private:
	//移動処理
	void Move();
	//回転処理
	void Rotate();
	//ダメージ処理
	void Damaged();
	//当たり判定結果のチェック
	void CheckCollider();
	//テキスト追加処理
	void AddLog(std::vector<TextStatus>& texts);
	//マップ移動後の座標に移動する処理
	void EnterRoom(ObjectType ExitType, Vector direction);
};