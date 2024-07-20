#include "DxLib.h"
#include "..\Collider\LineCollider.h"

//出入口
class ExitBase {
protected:
	//メンバ定数
	static const int THICKNESS = 10;//厚さ
	static const int WIDTH = 30;	//幅

	//メンバ変数
	std::vector<Ray2> lines;			//線分
	LineCollider* collider = nullptr;	//あたり判定
	Vector position = Vector(0, 0);		//座標
	int color = Color::WHITE;			//現在の色
	int next_map_id = 0;//繋がるマップのID
	

public:
	//コンストラクタ
	ExitBase(int exitMapId, int setColor);

	//デストラクタ
	virtual ~ExitBase();

	//アクセサ
	//当たり判定情報を返す
	inline LineCollider* getCollider() { return collider; }
	//線分配列を返す
	inline const std::vector<Ray2>& getLines() { return lines; }
	//座標を返す
	inline Vector getPosition() { return position; }
	//遷移先のマップのIDを返す
	inline int getNextStage() { return next_map_id; }

	//メンバ関数
	//更新処理
	void Prepare();
	//描画処理
	void Draw();
	//入場判定処理
	bool CheckEnter();
	
	//指定した出入口に対応する出入口を返す
	static ObjectType GetEnterType(ObjectType exitType);
};
