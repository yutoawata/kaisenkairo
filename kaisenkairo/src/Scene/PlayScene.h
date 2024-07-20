#pragma once
#include "..\Frame\Frame.h"
#include "..\BaseClass\SceneBase.h"
#include "..\ManagerClass\ColliderManager.h"
#include "..\ManagerClass\MapManager.h"
#include "..\ManagerClass\ObjectManager.h"
#include "..\Color\Color.h"

//ゲームプレイシーン
class PlayScene : public SceneBase {
private:
	//メンバ変数
	std::vector<std::string> texts = {//操作説明テキスト
		"目標:正しい順に色を巡れ!!",
		"",
		"移動:Wキー(前方向)・Sキー(後方向)",
		"     Aキー(左方向)・Dキー(右方向)",
		"視点移動:マウス",
		"ゲーム終了:ESCキー"
		
	};
	Frame* view_frame = new Frame(Vector(50.0f, 30.0f), 1200, 700);
	Frame* text_frame_01 = new Frame(Vector(50.0f, 800.0f), 850, 280, "ログ");
	Frame* text_frame_02 = new Frame(Vector(960.0f, 800.0f), 850, 280, "操作説明");
public:
	//コンストラクタ
	PlayScene(int fontSize = 32);

	//デストラクタ
	~PlayScene();

	//メンバ関数
	//更新処理
	void Update() override;
	//描画処理
	void Draw() override;
private:
	//ゲームリザルトチェック
	void CheckResult();
};