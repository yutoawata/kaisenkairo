#pragma once
#include "DxLib.h"

class FPSController {
private:
	//メンバ変数
	static const int MAX_FPS = 60;	//フレームレートの最大値
	static const float MAX_SECOND;	//1分間での最大秒数
	int start_time = 0;	//計測開始時の時間
	int count = 0;		//フレーム数のカウンター
	float fps = 0;		//フレームレート

	//コンストラクタ
	FPSController() {}
	FPSController(const FPSController& ) = delete;

public:
	//呼び出し処理
	static FPSController& Instance();

	//アクセサ
	inline float getDeltaTime() { return 1 / fps; }	//1フレームで経過した時間

	//メンバ関数
	//更新処理
	void Update();
	//1/60秒経つまで処理を一時停止
	void Wait();
};