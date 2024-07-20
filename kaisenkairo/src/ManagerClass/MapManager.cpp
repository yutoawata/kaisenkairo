#include "MapManager.h"

using namespace std;

//コンストラクタ
MapManager::MapManager() {
	//マップ情報を保存
	SetUpMap();
}

//デストラクタ
MapManager::~MapManager() {
	for (int i = 0; i < stage_id.size(); i++) {
		delete maps[stage_id[i]];
		delete up_exits[stage_id[i]];
		delete down_exits[stage_id[i]];
		delete right_exits[stage_id[i]];
		delete left_exits[stage_id[i]];
	}
}

//他ファイルでの呼び出し
MapManager& MapManager::Instance() {
	static MapManager Instance;
	return Instance;
}

void MapManager::Prepare() {
	maps[current_stage_id]->Prepare();
	up_exits[current_stage_id]->Prepare();
	down_exits[current_stage_id]->Prepare();
	right_exits[current_stage_id]->Prepare();
	left_exits[current_stage_id]->Prepare();
}

//更新処理
void MapManager::Update() {
	//カットインフラグ状態でないなら
	if (!is_cutin) {
		maps[current_stage_id]->Update();

		ChangeMap();
	}
	//カットイン状態なら
	else {
		CutIn();
		is_change = false;
	}
		
}

//描画処理
void MapManager::Draw() {
	if (!is_cutin) {
		maps[current_stage_id]->Draw();

		up_exits[current_stage_id]->Draw();
		down_exits[current_stage_id]->Draw();
		right_exits[current_stage_id]->Draw();
		left_exits[current_stage_id]->Draw();
	}
	else {
		//カラーバーを描画
		for (int i = 0; i < MAX_LINE_NUM; i++) {
			//カラーバーの中段を描画
			DrawBox(position.getPosX() + (width * i), position.getPosY() + up_height,
				position.getPosX() + (width * (i + 1)), position.getPosY() + middle_height,
				color_02[i],
				TRUE);
			//カラーバーの下段を描画
			DrawBox(position.getPosX() + (width * i), position.getPosY() + middle_height,
				position.getPosX() + (width * (i + 1)), position.getPosY() + down_height,
				color_03[i],
				TRUE);
			//現在のマップに対応するカラーバーである かつ　描画しないタイミングなら
			if (i == static_cast<int>(current_stage_id) && (cutin_timer < 0.5f
				|| (cutin_timer > 1.0f && cutin_timer < 1.5f)))
				continue;

			//カラーバーの上段を描画
			DrawBox(position.getPosX() + (width * i), position.getPosY(),
				position.getPosX() + (width * (i + 1)), position.getPosY() + up_height,
				color_01[i],
				TRUE);
		}
	}
}

//出口の座標を返す
Vector MapManager::getExitPosition(ObjectType type) {
	switch (type) {
	case ObjectType::UP_EXIT:
		//上の出入口の座標を返す
		return up_exits[current_stage_id]->getPosition();
		break;
	case ObjectType::DOWN_EXIT:
		//上の出入口の座標を返す
		return down_exits[current_stage_id]->getPosition();
		break;
	case ObjectType::RIGHT_EXIT:
		//上の出入口の座標を返す
		return right_exits[current_stage_id]->getPosition();
		break;
	case ObjectType::LEFT_EXIT:
		//上の出入口の座標を返す
		return left_exits[current_stage_id]->getPosition();
		break;
	default://対応してない種類なら
		return Vector(0, 0);//原点(ありえない値)を返す
		break;
	}
}

//マップ番号配列をint型配列として返す
vector<int> MapManager::getIntStageNum() {
	vector<int> map_num;//返す配列
	for (int i = 0; i < stage_id.size();i++) {
		map_num.emplace_back(static_cast<int>(stage_id[i]));//int型にキャストして保存
	}
	return map_num;
}

//異なるマップに移動した際のカットイン処理
void MapManager::CutIn() {
	//カットイン中の経過時間を快速
	cutin_timer += FPSController::Instance().getDeltaTime();
	
	//カットインの描画時間を過ぎたら
	if (cutin_timer > CUTIN_TIME) {
		is_cutin = false;
		cutin_timer = 0;//経過時間の計測をリセット
	}
}

//各マップごとの線分情報を読み込む
void MapManager::SetUpMap() {
	//マップ情報の生成
	for (int i = 0; i < stage_id.size(); i++) {
		int stage_num = i;
		std::vector<Ray2> lines = LoadMapInfo(field_03, stage_id[i], stage_num++);
		maps[stage_id[i]] = new Map(lines, color_01[(int)stage_id[i]]);
	}

	UpdateLines();		//現在のマップ情報を更新
	UpdateCollider();	//当たり判定情報を更新
}

//現在のマップの線分情報の更新
void MapManager::UpdateLines() {
	is_change = true;	//マップ遷移フラグをtrueにする
	is_cutin = true;	//マップ遷移なのでカットインフラグをtrueにする
}

//マップ遷移処理
void MapManager::ChangeMap() {
	//上向きの出入口にプレイヤーが衝突したら
	if (up_exits[current_stage_id]->CheckEnter()) {
		current_stage_id = (MapNum)up_exits[current_stage_id]->getNextStage();//現在のマップIDの更新
		UpdateCollider();	//出入口のコライダーを更新
		UpdateLines();		//マップの線分情報を保存
	}
	//下向きの出入口にプレイヤーが衝突したら
	else if (down_exits[current_stage_id]->CheckEnter()) {
		current_stage_id = (MapNum)down_exits[current_stage_id]->getNextStage();//現在のマップIDの更新
		UpdateCollider();	//出入口のコライダーを更新
		UpdateLines();		//マップの線分情報を保存
	}
	//右向きの出入口にプレイヤーが衝突したら
	else if (right_exits[current_stage_id]->CheckEnter()) {
		current_stage_id = (MapNum)right_exits[current_stage_id]->getNextStage();//現在のマップIDの更新
		UpdateCollider();	//出入口のコライダーを更新
		UpdateLines();		//マップの線分情報を保存
	}
	//左向きの出入口にプレイヤーが衝突したら
	else if (left_exits[current_stage_id]->CheckEnter()) {
		current_stage_id = (MapNum)left_exits[current_stage_id]->getNextStage();//現在のマップIDの更新
		UpdateCollider();//出入口のコライダーを更新
		//マップの線分情報を保存
		UpdateLines();
	}
}

//各コライダー情報の登録処理
void MapManager::UpdateCollider() {
	ColliderManager::Instance().ClearColliders();
	//更新したコライダーをCollider管理クラスに渡す
	ColliderManager::Instance().AddList(maps[current_stage_id]->getCollider());
	ColliderManager::Instance().AddList(up_exits[current_stage_id]->getCollider());
	ColliderManager::Instance().AddList(down_exits[current_stage_id]->getCollider());
	ColliderManager::Instance().AddList(right_exits[current_stage_id]->getCollider());
	ColliderManager::Instance().AddList(left_exits[current_stage_id]->getCollider());
}

//出入口を生成
int MapManager::AddStageNum(int stageNum) {
	stageNum++;//マップ番号を進める

	//マップ番号がマップ数を超えたら
	if (stageNum == stage_id.size())
		stageNum = 0;//マップ番号をリセット

	return stageNum;
}

//直線の線分情報を生成
Ray2 MapManager::GetStraightLine(Vector root, int lineColor, bool is_horizontal) {
	Vector start, end;
	float offset = GRID_LENGTH / 2;
	//横線を生成するならなら
	if (is_horizontal == true) {
		start = Vector(root + Vector(0.0f, offset));	//視点
		end = Vector(start + Vector(GRID_LENGTH, 0));	//終点
	}
	//縦線を生成するなら
	else {
		start = Vector(root + Vector(offset, 0.0f));	//視点
		end = Vector(start + Vector(0, GRID_LENGTH));	//終点
	}
	return Ray2(start, end, lineColor);
}

//角の線分情報を生成
void MapManager::GetCornerLine(vector<Ray2>& lines, Vector root, int lineColor, bool is_up, bool is_right) {
	//基準点と壁の長さを保存
	float horizontal_offset = GRID_LENGTH / 2;
	float vartical_offset = GRID_LENGTH / 2;
	Vector start = Vector(root + Vector(horizontal_offset, horizontal_offset));

	//角の横線を計算
	horizontal_offset = is_right ? -horizontal_offset : horizontal_offset;
	Vector end = Vector(start + Vector(horizontal_offset, 0.0f));
	//線を生成
	Ray2 horizontal_line(start, end, lineColor);
	//配列に保存
	lines.emplace_back(horizontal_line);

	//角の縦線の計算
	vartical_offset = is_up ? vartical_offset : -vartical_offset;
	end = Vector(start + Vector(0.0f, vartical_offset));
	Ray2 vertical_line(start, end, lineColor);
	lines.emplace_back(vertical_line);
}

//マップチップに対応した線分情報を生成
void MapManager::CreateMap(vector<Ray2>& lines, Chip_Kind kind, int pos_x, int pos_y, MapNum mapNum, int& stageNum) {
	Ray2 line;//生成した線分情報
	int map_num = static_cast<int>(mapNum);
	int color = color_01[static_cast<int>(mapNum)];//各してーじの描画時の色
	Vector MapPos = Vector(LEFT_LIMIT, UP_LIMIT);//マップの基準座標(左上)
	//グリッド単位の基準座標(左上)
	Vector root = Vector(MapPos + Vector(GRID_LENGTH * pos_x, GRID_LENGTH * pos_y));
	switch (kind) {
	case Chip_Kind::NONE_LINE://線分無し
		break;
	case Chip_Kind::VARTICAL://縦線
		line = GetStraightLine(root,  color, false);
		lines.emplace_back(line);
		break;
	case Chip_Kind::HORIZONTAL://横線
		line = GetStraightLine(root,  color, true);
		lines.emplace_back(line);
		break;
	case Chip_Kind::LEFT_UP_CORNER://左上(四角形基準)の角
		GetCornerLine(lines, root,  color, true, false);
		break;
	case Chip_Kind::RIGHT_UP_CORNER://右上(四角形基準)の角
		GetCornerLine(lines, root,  color, true, true);
		break;
	case Chip_Kind::LEFT_DOWN_CORNER://左下(四角形基準)の角
		GetCornerLine(lines, root,  color, false, false);
		break;
	case Chip_Kind::RIGHT_DOWN_CORNER://右下(四角形基準)の角
		GetCornerLine(lines, root,  color, false, true);
		break;
	case Chip_Kind::UP_EXIT://上向きの出入り
		stageNum = AddStageNum(stageNum);
		//各ステージの出入口を保存
		up_exits[stage_id[map_num]] = new UpExit(root, static_cast<int>(stage_id[stageNum]), color_01[stageNum]);
		//マップの線分情報に出入口の情報を追加
		InsertLines(lines, up_exits[mapNum]->getLines());
		break;
	case Chip_Kind::DOWN_EXIT://上向きの出入り
		stageNum = AddStageNum(stageNum);
		//各ステージの出入口を保存
		down_exits[stage_id[map_num]] = new DownExit(root, static_cast<int>(stage_id[stageNum]), color_01[stageNum]);
		//マップの線分情報に出入口の情報を追加
		InsertLines(lines, down_exits[mapNum]->getLines());
		break;
	case Chip_Kind::RIGHT_EXIT://上向きの出入り
		stageNum = AddStageNum(stageNum);
		//各ステージの出入口を保存
		right_exits[stage_id[map_num]] = new RightExit(root, static_cast<int>(stage_id[stageNum]), color_01[stageNum]);
		//マップの線分情報に出入口の情報を追加
		InsertLines(lines, right_exits[mapNum]->getLines());
		break;
	case Chip_Kind::LEFT_EXIT://上向きの出入り
		stageNum = AddStageNum(stageNum);
		//各ステージの出入口を保存
		left_exits[stage_id[map_num]] = new LeftExit(root, static_cast<int>(stage_id[stageNum]), color_01[stageNum]);
		//マップの線分情報に出入口の情報を追加
		InsertLines(lines, left_exits[mapNum]->getLines());
		break;
	case Chip_Kind::ENEMY_POSITION://歴の座標
		//対応するグリッド内の中心を座標として代入
		enemy_positions[mapNum].emplace_back(root + Vector(GRID_LENGTH / 2, GRID_LENGTH / 2));
		break;
	default:
		break;
	}
}

vector<Ray2> MapManager::LoadMapInfo(int mapChips[FIELD_HIGHT][FIELD_WIDTH], MapNum mapNum, int stageNum) {
	std::vector<Ray2> lines;//生成したマップの線分情報
	int wall_color = color_01[static_cast<int>(mapNum)];//ステージの描画時の色
	
	for (int y = 0; y < FIELD_HIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			//マップチップに応じた線分の生成
  			CreateMap(lines, (Chip_Kind)mapChips[y][x], x, y, mapNum, stageNum);
		}
	}
	//外壁の線分を生成・保存
	Ray2 line;
	line = Ray2(Vector(LEFT_LIMIT, UP_LIMIT), Vector(RIGHT_LIMIT, UP_LIMIT), wall_color);
	lines.emplace_back(line);
	line = Ray2(Vector(RIGHT_LIMIT, UP_LIMIT), Vector(RIGHT_LIMIT, DOWN_LIMIT), wall_color);
	lines.emplace_back(line);
	line = Ray2(Vector(LEFT_LIMIT, DOWN_LIMIT), Vector(RIGHT_LIMIT, DOWN_LIMIT), wall_color);
	lines.emplace_back(line);
	line = Ray2(Vector(LEFT_LIMIT, UP_LIMIT), Vector(LEFT_LIMIT, DOWN_LIMIT), wall_color);
	lines.emplace_back(line);

  	return lines;//生成した線分情報を返す
}