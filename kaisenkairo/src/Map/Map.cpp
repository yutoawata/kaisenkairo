#include "Map.h"

//コンストラクタ
Map::Map(std::vector<Ray2> setLines, int setColor, Vector setPos)
	: ObjectBase(setPos) {
	position = setPos;
	lines = setLines;
	color = setColor;
	collider = new LineCollider(setLines, position, ObjectType::WALL);
}

//デストラクタ
Map::~Map() {}

//更新前処理
void Map::Prepare() {
	collider->Reset();//当たり判定情報のリセット
}

//更新処理
void Map::Update() {
	Search();//索敵処理
}

//描画処理
void Map::Draw() {
	//マップを描画
	for (int i = 0; i < lines.size(); i++) {
		DrawLine(lines[i].getBegin().getPosX(), lines[i].getBegin().getPosY(),	//始点 
				 lines[i].getEnd().getPosX(),	lines[i].getEnd().getPosY(),	//終点
				 Color::WHITE//描画時の色
		);
	}
}

void Map::Search() {
	if (CheckHitKey(KEY_INPUT_R))
		is_search = true;

	if (is_search) {
		if (timer >= 300) {
			is_search = false;
			timer = 0;
		}
	}
}