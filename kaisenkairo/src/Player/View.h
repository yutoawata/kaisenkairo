#pragma once
#include "DxLib.h"
#include "..\GameSystem\FPSController.h"
#include "..\ManagerClass\mapmanager.h"
#include "..\Math\Methods.h"

//視界描画クラス
class View {
private:
	//メンバ定数
	static const int MAX_NOISE_NUM = 100;//描画するノイズの最大値(配列の要素数シテイに使用するためstatic定数にする)
	const int MIN_NOISE_NUM = 0;		//描画するノイズの最小値
	const int RAY_NUM = 300;			//描画に使用する線分の本数
	const int HEIGHT_LIMIT = 700;		//描画する高さの限界
	const int MIN_X = 50;
	const int MIN_Y = 30;
	const float ADD_NOISE_INTERVAL = 0.2f;

	//メンバ変数
	Vector noise_pos[MAX_NOISE_NUM] = {};//ノイズを描画する座標
	Vector min_pos = Vector(50, 30);//ノイズの座標の成分の下限
	Vector max_pos = Vector(1250.0f - width, 730.0f - height);//ノイズの座標の成分の上限
	int noise_num = 0;		//ノイズの個数カウンター
	int range = 700;		//視野の距離
	int width = 100;		//ノイズの横幅
	int height = 60;		//ノイズの縦幅
	int min_x = 50;
	int min_y = 30;
	int max_x = 1250 - width;
	int max_y = 730 - height;
	float timer = 0;		//ノイズ描画時の経過時間

public:
	//コンストラクタ
	View();

	//メンバ関数
	//描画処理
	void Draw(Vector playerPos, float playerAngle);
	//ダメージを受けていつ時のの椅子を描画
	void DrawNoise(bool isAddNoise);
private:
	//プレイヤの視界をマップに描画
	void DrawViewRenge(Vector playerPos, Vector crossPos);
	//一人称視点を描画
	void DrawFPSView(int lineNum, int lineColor, float viewHeight);
	//壁の奥が透けないようににプレイヤーの視野を一番近い交点を探す
	Vector CheckMinDistanceWall(Ray2 ray, Vector playerpos, int& color);
};