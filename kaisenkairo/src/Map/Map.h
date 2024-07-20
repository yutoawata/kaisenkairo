#pragma once
#include <vector>
#include "DxLib.h"
#include "..\Color\Color.h"
#include "..\Math\Methods.h"
#include "..\BaseClass\ObjectBase.h"
#include "..\Collider\LineCollider.h"
#include "Exit.h"

class Map : public ObjectBase {
private:
	//メンバ変数
	LineCollider* collider;	//壁の当たり判定
	std::vector<Ray2> lines;//mapの線分情報の配列
	bool is_search = false;	//サーチ機能を使用しているかのフラグ
	int timer = 0;			//サーチ中の経過時間を計測
	int radius = 0;			//サーチ範囲の半径

public:
	//コンストラクタ
	Map(std::vector<Ray2> setLines, int setColor, Vector setPos = Vector(1400, 30));
	~Map();

	//アクセサ
	inline LineCollider* getCollider() { return collider; }	//mapの当たり判定情報を返す
	inline const std::vector<Ray2>& getLines() { return lines; }//線文情報を返す
	inline int getSize() { return static_cast<int>(lines.size()); }			//線分配列の要素数を返す

	//メンバ関数
	//更新前処理
	void Prepare() override;
	//更新処理
	void Update() override;
	//描画処理
	void Draw() override;
	//マップギミック
	void Search();
};