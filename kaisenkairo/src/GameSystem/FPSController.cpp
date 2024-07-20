#include "FPSController.h"

const float FPSController::MAX_SECOND = 60.0f;

//呼び出し処理
FPSController& FPSController::Instance() {
	static FPSController instance;
	return instance;
}

//更新処理
void FPSController::Update() {
	if (count == 0)
		//ミリ秒単位の精度を持つカウンタの現在値を得る
		start_time = GetNowCount();
	if (count == MAX_FPS) {
		//ミリ秒単位の制度を持つカウンタの現在値を得る
		int current_time = GetNowCount();
		//フレームレートを算出
		fps = 1000.f / ((current_time - start_time) /MAX_SECOND);
		count = 0;		//カウントをリセット
		start_time = current_time;	//開始時間を更新
	}
	count++;//1秒間のフレーム数をカウント
}

//1/60秒経つまで処理を一時停止
void FPSController::Wait() {
	//ミリ秒単位の制度を持つカウンタの現在値を得る
	int took_time = GetNowCount() - start_time;
	//処理の待機時間を算出
	int wait_time = count * 1000 / MAX_FPS - took_time;
	//待機時間があるなら
	if (wait_time > 0)
		//処理を個kで指定時間止める
		Sleep(wait_time);
}