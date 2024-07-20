#include "ObjectManager.h"

using namespace std;

//コンストラクタ
ObjectManager::ObjectManager() {}

//デストラクタ
ObjectManager::~ObjectManager() {
	delete player;
	for (int i = 0; i < enemys.size(); i++) {
		delete enemys[i];
	}
}

//他ファイルでの呼び出し用関数
ObjectManager& ObjectManager::Instance() {
	static ObjectManager instance;
	return instance;
}

//プレイヤー関連のクラスを初期化
void ObjectManager::EntryPlayer(int logFontSize) {
	delete player;
	player = new Player(Vector(1600, 750),0,logFontSize);//プレイヤーオブジェクトを初期化
}

//敵クラスを初期化
void ObjectManager::EntryEnemy() {
	//マップ管理クラスから遷移後のマップのエネミーの座標配列を取得
	vector<Vector> positions = MapManager::Instance().getEnemyPosition();
	int enemys_size = static_cast<int>(enemys.size());
	for (int i = 0; i < enemys_size; i++)
		delete enemys[i];//遷移前のエネミーを削除

	enemys.clear();//削除したエネミーのポインタを削除
	for (Vector position : positions) 
		enemys.emplace_back(new Enemy(position));
}

//ゲームのプレイ結果
ObjectManager::ResultStatus ObjectManager::CheckResult(vector<int> stageId) {
	//プレイヤーが進んだマップの順番が正しいなら
	if (player->CheckGoal(stageId)) 
		return ResultStatus::CLEAR;//クリア

	//プレイヤーが進んだマップの順番が間違っている　または　プレイヤーのHPが0になったなら
	if (player->gethitPoint() == 0) 
		return ResultStatus::GAME_OVER;//ゲームオーバー
	
	//条件を満たしてないので
	return ResultStatus::PLAY;//ゲームを続行
}

//更新前処理
void ObjectManager::Prepare() {
	player->Prepare();//プレイヤークラスの更新前処理

	for (int i = 0; i < enemys.size(); i++)
		enemys[i]->Prepare();//各敵クラスの更新前処理
	
}

//更新処理
void ObjectManager::Update() {
	//マップが遷移したなら
	if (MapManager::Instance().getIsChange()) 
		//遷移後のマップマップ情報にあったエネミーを生成
		EntryEnemy();
	
	player->Update();//プレイヤークラスの更新処理

	for (int i = 0; i < enemys.size(); i++) 
		enemys[i]->Update();//各敵クラスの更新処理
	
}

//描画処理
void ObjectManager::Draw() {
	player->Draw();//プレイヤーの描画処理
}