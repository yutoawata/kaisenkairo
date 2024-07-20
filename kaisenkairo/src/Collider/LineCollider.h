#pragma once
#include "..\BaseClass\ColliderBase.h"

//線の当たり判定コライダークラス
class LineCollider : public ColliderBase {
private:
	//メンバ変数
	std::vector<Ray2> lines;	//線分情報(始点・終点・色)
public:

	//コンストラクタ
	LineCollider(std::vector<Ray2> setLines, Vector setPos, ObjectType setType);

	//デストラクタ
	~LineCollider();

	//アクセサ
	//線分情報を返す
	inline const std::vector<Ray2>& getLines() { return lines; }

	//メンバ関数
	//座標の更新処理
	void UpdateLines(std::vector<Ray2> newLines);
};