#pragma once
#include <cmath>
#include <string>
#include "DxLib.h"
#include "..\Map\Exit.h"
#include "..\GameSystem\FPSController.h"
#include "..\Map\Map.h"
#include "..\Color\Color.h"
#include "ColliderManager.h"




class MapManager {
private:
	enum class MapNum {
		MAP_01,
		MAP_02,
		MAP_03,
		MAP_04,
		MAP_05,
		MAP_06,
		MAP_07
	};
	enum class Chip_Kind {
		NONE_LINE,			//マップチップ無し
		VARTICAL,			//縦線
		HORIZONTAL,			//横線
		LEFT_UP_CORNER,		//左上の角
		RIGHT_UP_CORNER,	//右上の角
		LEFT_DOWN_CORNER,	//左下の角
		RIGHT_DOWN_CORNER,	//右下の角
		UP_EXIT,			//出口(上の壁)
		DOWN_EXIT,			//出口(下の壁)
		RIGHT_EXIT,			//出口(右の壁)
		LEFT_EXIT,			//出口(左の壁)
		ENEMY_POSITION,		//敵オブジェクトの位置
	};
	//メンバ定数
	const std::vector<MapNum> stage_id//マップの順番
		= { MapNum::MAP_01, MapNum::MAP_02, MapNum::MAP_03, MapNum::MAP_04, MapNum::MAP_05, MapNum::MAP_06, MapNum::MAP_07 };
	static const int MAX_LINE_NUM = 7;	//カットイン時のカラーバーの本数
	static const int CUTIN_TIME = 2;	//カットインを何秒するか
	static const int FIELD_WIDTH = 17;	//マップチップの列数
	static const int FIELD_HIGHT = 25;	//マップチップの行数
	static const int UP_LIMIT = 30;		//マップチップの座標のY軸下限
	static const int DOWN_LIMIT = 780;	//マップチップの座標のY軸上限
	static const int RIGHT_LIMIT = 1910;//マップチップの座標のX軸上限
	static const int LEFT_LIMIT = 1400;	//マップチップの座標のX軸下限
	static const int GRID_LENGTH = 30;	//マップチップの大きさ

	//メンバ変数
	//マップチップ③
	int field_03[FIELD_HIGHT][FIELD_WIDTH] = {
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 3, 2, 2, 2, 4, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,11, 0, 1, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0,},
	{0, 0, 0, 0,11, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0,},
	{2, 2, 2, 2, 2, 6, 0, 0, 0, 0, 0, 5, 2, 2, 2, 6, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 3, 2, 2, 4, 0, 0, 0, 0, 0, 0,},
	{10,0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,},
	{0, 0, 3, 2, 2, 4, 0, 1, 0, 0, 5, 2, 2, 2, 4, 0, 0,},
	{0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0,},
	{0, 0, 1, 0,11, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0,},
	{0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0,11, 0, 1, 0, 0,},
	{0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 3, 2, 2, 2, 6, 0, 0,},
	{0, 0, 5, 2, 2, 6, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 9,},
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 5, 2, 2, 6, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	};
	
	std::unordered_map<MapNum, Map*> maps;//各マップのクラス
	std::unordered_map<MapNum, UpExit*> up_exits;		//各マップの上で入り口クラス
	std::unordered_map<MapNum, DownExit*> down_exits;	//各マップの上で入り口クラス
	std::unordered_map<MapNum, RightExit*> right_exits;	//各マップの上で入り口クラス
	std::unordered_map<MapNum, LeftExit*> left_exits;	//各マップの上で入り口クラス
	std::unordered_map<MapNum, std::vector<Vector>> enemy_positions;//各マップの敵の位置座標
	unsigned int color_01[MAX_LINE_NUM]//カラーバーの上段の色(マップの色も同様)
		= { Color::WHITE, Color::YELLOW, Color::LIGHT_BLUE, Color::GREEN, Color::PURPLE, Color::RED, Color::BLUE };
	unsigned int color_02[MAX_LINE_NUM]//カラーバーの中段の色
		= { Color::BLOCK, Color::BLUE,Color::PURPLE,Color::BLOCK, Color::LIGHT_BLUE, Color::BLOCK, Color::WHITE };
	unsigned int color_03[MAX_LINE_NUM]//カラーバーの下段の色
		= { Color::DARK_BLUE, Color::BLOCK, Color::DARK_BLUE, Color::BLOCK, Color::BLOCK, Color::BLOCK, Color::BLOCK };

	Vector position = Vector(0, 0);	//Mapの座標
	MapNum current_stage_id = MapNum::MAP_01;//現在のマップのID
	int width = 274;		//カラーバーの横幅
	int up_height = 810;	//上段カラーバーの縦幅
	int middle_height = 67 + up_height;		//中段カラーバーの縦幅
	int down_height = 203 + middle_height;	//下段カラーバーの縦幅
	float cutin_timer = 0;	//カットイン時の経過時間
	bool is_close = true;	//ミニマップか閉じてあるかのフラグ
	bool is_sliding = false;//ミニマップが開閉中であるかのフラグ
	bool is_change = false;	//マップ遷移フラグ
	bool is_cutin = false;	//カットインフラグ

	//コンストラクタ
	MapManager();
	MapManager(const MapManager&) = delete;

public:
	//デストラクタ
	~MapManager();

	//他ファイルでの呼び出し
	static MapManager& Instance();

	//アクセサ
	//現在の敵クラスの座標を返す
	inline std::vector<Vector> getEnemyPosition() { return enemy_positions[current_stage_id]; }
	//現在のマップの線分情報を返す
	inline std::vector<Ray2> getMapLines() { return maps[current_stage_id]->getLines(); }
	//マップIDの配列を返す
	inline std::vector<MapNum> getStageId() { return stage_id; }
	//マップIDをint型の配列で返す
	std::vector<int> getIntStageNum();
	//指定した種類の出入口の座標を返すを返す
	Vector getExitPosition(ObjectType type);
	//現在のマップのIDをint型で返す
	inline int getCurrentStageId() { return static_cast<int>(current_stage_id); }
	//マップ遷移フラグを返す
	inline bool getIsChange() { return is_change; }
	//カットインフラグを返す
	inline bool getIsCutin() { return is_cutin; }
public:

	//メンバ関数
	//マップ情報の準備
	void SetUpMap();
	//更新前処理
	void Prepare();
	//更新処理
	void Update();
	//描画処理
	void Draw();
private:
	//マップ遷移処理
	void ChangeMap();
	//線分情報の更新処理
	void UpdateLines();	
	//当たり判定情報の更新処理
	void UpdateCollider();
	//カットイン処理
	void CutIn();
	//番号を加算
	int AddStageNum(int stageNum);
	//角を作成
	void GetCornerLine(std::vector<Ray2>& lines, Vector root, int lineColor, bool is_up, bool is_right);
	//マップチップごとの生成関数呼び出し
	void CreateMap(std::vector<Ray2>& lines, Chip_Kind kind, int pos_x, int pos_y, MapNum mapNum, int& stageNum);
	//MapChipを線分クラスの配列に変換する関数
	std::vector<Ray2> LoadMapInfo(int mapChips[FIELD_HIGHT][FIELD_WIDTH], MapNum mapNum, int stageNum);
	//縦線・横線を作成
	Ray2 GetStraightLine(Vector root, int lineColor, bool is_horizontal);
};