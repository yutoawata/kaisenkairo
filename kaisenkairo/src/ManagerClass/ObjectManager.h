#pragma once
#include "DxLib.h"
#include "..\Player\Player.h"
#include "..\Player\View.h"
#include "..\Enemy\Enemy.h"
#include "..\Text\GameText.h"
#include "MapManager.h"

class ObjectManager {
public:
	//ゲーム進捗状況の列挙型
	enum class ResultStatus {
		PLAY,		//ゲーム進行中
		CLEAR,		//ゲームクリア
		GAME_OVER	//ゲームオーバー
	};

private:
	//メンバ変数
	std::vector<Enemy*> enemys;	//敵対Objectのクラス
	Player* player = nullptr;	//プレイヤークラス

	//コンストラクタ
	ObjectManager();
	//コピーコンストラクタを削除(Shingletonパターン)
	ObjectManager(const ObjectManager&) = delete;
public:
	//デストラクタ
	~ObjectManager();

	//他ファイルでの呼び出し用関数
	static ObjectManager& Instance();
	//アクセサ
	//プレイヤクラスを返す
	inline Player getPlayer() { return *player; }		
	inline Vector getPlayerPosition() { return player->getPosition(); }

	//メンバ関数
	//更新前処理
	void Prepare();
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//敵対オブジェクトクラス生成関数
	void EntryEnemy();
	//プレイヤークラス生成関数
	void EntryPlayer(int logFontSize);
	//ゲーム進捗状況の判定関数
	ResultStatus CheckResult(std::vector<int>stageId);
};