#include "Player.h"

using namespace std;

//コンストラクタ
Player::Player(Vector setPos, int setAngle, int fontSize)
	:ObjectBase(setPos, Color::YELLOW) {
	collider = new CircleCollider(position, RADIUS, ObjectType::PLAYER);
	ColliderManager::Instance().AddList(collider);
	route.emplace_back(0);
	view = new View();
	/*
		AddLogを呼び出すラムダ式を渡すことで、
		メンバ関数をクラスを指定していない関数ポインタとして渡す
	*/
	std::function<void(std::vector<TextStatus>&)> set_func =
		[this](std::vector<TextStatus>& texts) {AddLog(texts); };
	std::vector<std::string> texts = { " "," "," "," "," " };
	log = new GameText(Vector(50, 840), texts, Color::WHITE, fontSize, set_func);
}

//デストラクタ
Player::~Player() {
	delete log;
	delete view;
	delete collider;
}

//更新前処理
void Player::Prepare() {
	is_move = false;
	is_damage = false;
	collider->Reset();
	Move();
	Rotate();
	/*
		ここで移動処理を行うのは、衝突処理を実装するにあたり、
		移動処理と、座標の更新の間に当たり判定処理を行いたいため。
	*/
}

//更新処理
void Player::Update() {
	CheckCollider();

	if (is_move) {
		//移動時間を計測
		move_timer += FPSController::Instance().getDeltaTime();
		position = collider->getPosition();//座標を更新
	}
	else
		collider->UpdatePosition(position);//移動できないので元の座標に戻す

	Damaged();		//ダメージ処理
	log->Update();	//ログの更新処理
}

//描画処理
void Player::Draw() {
	view->Draw(position, angle);//一人称視点を描画
	view->DrawNoise(is_damage);	//ダメージ状態の描画
	log->Draw();//行動ログの描画

	//自身の座標を円で表示
	DrawCircle(position.getPosX(), position.getPosY(), RADIUS, color, TRUE);
}


//表示するテキストを追加
void Player::AddLog(vector<TextStatus>& texts) {
	//2秒間移動したなら
	if (move_timer >= ADD_LOG_INTERVAL) {
		texts.insert(texts.begin(), TextStatus("ザザァ.....", Color::WHITE));
		move_timer = 0.0f;//移動時間をリセット
	}
	//hit_pointが100・50のいずれかになったなら
	if (hit_point % HALF_HIT_POINT == 0&& can_add_log) {
		//表示するテキストを作成
		string new_text = "現在のHP:" + to_string(hit_point);
		
		if (hit_point == MAX_HIT_POINT)
			texts.insert(texts.begin(), TextStatus(new_text, Color::GREEN));//上記の内容を配列の最後尾に追加
		else if(hit_point==HALF_HIT_POINT)
			texts.insert(texts.begin(), TextStatus(new_text, Color::RED));//上記の内容を配列の最後尾に追加
		
		
		can_add_log = false;
	}

	if (texts.size() > MAX_LOG_LINE)
		texts.erase(texts.end() - 1);
}

//移動処理
void Player::Move() {
	Vector move_pos = position;//移動先の座標
	
	if (CheckHitKey(KEY_INPUT_A)) {
		is_move = true;
		//左方向の方向ベクトルを算出
		Vector left = CreateVector(angle - static_cast<float>(M_PI_2), MOVE_SPEED);
		move_pos = move_pos - left;//左方向に移動
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		is_move = true;
		//移動方向を計算
		Vector right = CreateVector(angle + static_cast<float>(M_PI_2), MOVE_SPEED);
		move_pos = move_pos - right;//右方向に移動
	}
	if (CheckHitKey(KEY_INPUT_W)) {
		is_move = true;
		//移動方向ベクトルを算出
		Vector forward = CreateVector(angle, MOVE_SPEED);
		move_pos = move_pos - forward;//前方向に移動
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		is_move = true;
		//移動方向を計算
		Vector back = CreateVector(angle - static_cast<float>(M_PI), MOVE_SPEED);
		move_pos = move_pos - back;//後ろ方向に移動
	}

	//コライダーに移動後の座標を代入
	collider->UpdatePosition(move_pos);
}

//回転処理
void Player::Rotate() {
	//マウスカーソルの座標成分
	int cursor_x, cursor_y;
	//マウスカーソルの位置を取得
	GetMousePoint(&cursor_x, &cursor_y);

	//中心より右入力なら
	if (960 < cursor_x)
		//右を振り向く
		angle += static_cast<float>(M_PI_4) / ROTATE_SPEED;
	//中心より左入力なら
	else if (960 > cursor_x) 
		//左を振り向く
		angle -= static_cast<float>(M_PI_4) / ROTATE_SPEED;

	//角度が一周したら
	if (angle > static_cast<float>(M_PI) * 2)
		//一週分の角度を引く
		angle -= static_cast<float>(M_PI) * 2;
}

//当たった場合の処理
void Player::CheckCollider() {
	//当たった相手の種類を検索
	for (ColliderBase other : collider->getOthers()) {
		ObjectType other_type = other.getType();
		//壁に当たっていれば
		if (other_type == ObjectType::WALL)
			//移動フラグをfalseに
			is_move = false;
		
		else if (other_type == ObjectType::UP_EXIT || other_type == ObjectType::DOWN_EXIT ||
			other_type == ObjectType::RIGHT_EXIT || other_type == ObjectType::LEFT_EXIT) {
			is_move = false;//移動フラグをfalseに;
			//当たった相手の座標を取得
			Vector direction = other.getPosition() - position;
			//マップ間移動処理を行う
			EnterRoom(other_type, direction);
		}
		else if (other_type == ObjectType::ENEMY)
			is_damage = true;
	}
}

void Player::Damaged() {

	if (is_damage) {
		//経過時間を計測
		timer += FPSController::Instance().getDeltaTime();
		//0.5秒毎にHitPointを1減らす
		if (timer >= DAMAGE_INTERVAL) {
			can_add_log = true;
			hit_point--;//HPを減らす
			timer = 0;	//経過時間をリセット
		}
	}
	//ダメージを受けていないなら
	else {
		//HPの上限に達していないなら
		if (hit_point != MAX_HIT_POINT) {
			//経過時間を計測
			timer += FPSController::Instance().getDeltaTime();
			////0.5秒毎にHitPointを1減らす
			if (timer >= DAMAGE_INTERVAL) {
				can_add_log = true;
				hit_point++;//HPを増やす
				timer = 0;	//経過時間をリセット
			}
		}
	}
}

//マップ間の移動時の処理
void Player::EnterRoom(ObjectType exitType, Vector direction) {
	Vector enter_position = Vector(0, 0);//移動先の入り口の座標
	enter_position = MapManager::Instance().getExitPosition(ExitBase::GetEnterType(exitType));

	float melt_value = 2.0f;
	//次のステージに移動時入り口と接触した状態でスタートしないように移動量のベクトルを倍にするする
	Vector enter_direction = Vector(direction.getX() * melt_value, direction.getY() * melt_value);
	position = direction + enter_position;	//移動後の座標を代入
	collider->UpdatePosition(position);		//コライダーの座標を更新
	int num = MapManager::Instance().getCurrentStageId();//移動先のマップ番号を取得
	route.emplace_back(num);//マップ番号を移動したルートに保存
}


//ゴールしたかのチェック
bool Player::CheckGoal(vector<int> stageId) {
	int num = 0;//検索しているマップの順番
	//通ったmapの順番を検索
	for (int map : route) {
		//通ったマップの順番が違うなら
		if (map != stageId[num]) {
			route.clear();//順序をリセット
			return false;
		}
		num++;
	}

	//通ったマップの順番が途中なら
	if (route.size() != stageId.size())
		return false;

	//いずれの条件にも該当しないなら
	return true;
}