#include "View.h"

using namespace std;

//コンストラクタ
View::View() {
	//ノイズの描画座標を乱数で生成
	for (int i = 0; i < MAX_NOISE_NUM; i++) {
		noise_pos[i] = Vector(CreateRandom(min_x, max_x), CreateRandom(min_y, max_y));
	}
}

Vector View::CheckMinDistanceWall(Ray2 viewRay, Vector playerPos, int& color) {
	vector<Ray2> map_lines = MapManager::Instance().getMapLines();//mapの線分情報のコピー
	Vector min_dist_cross = Vector(NULL, NULL);//最短距離の交点の座標
	float min_dist = 0;		//最短距離
	bool is_first = true;	//一つ目の交点かのフラグ

	//mapの線分情報をfor文で一本ずつ確認して行く
	for (int i = 0; i < map_lines.size(); i++) {
		Vector cross_pos = Intersection(map_lines[i], viewRay);//視界判定の線分mapの線分との交点
		Vector distance_vec = cross_pos - playerPos;
		float distance = distance_vec.getSize();
		//交点が発生していたなら
		if (!cross_pos.IsZero()) {
			//一個目の交点なら
			if (is_first) {
				min_dist_cross = cross_pos;		//基準とするために最短距離の交点の値に代入する
				color = map_lines[i].getColor();//一番近い交点が更新されたら描画する線分の色を更新
				min_dist = distance;//基準とするために距離の最小値の値に代入する
				is_first = false;	//以降の交点は一つ目ではないのでフラグを切る
			}
			//二つ目以降の交点 かつ　保存された最短距離より短いなら
			else if (!is_first && distance < min_dist) {
				min_dist_cross = cross_pos;			//最短距離の交点の座標を更新
				min_dist = distance;				//最短距離の値を更新
				color = map_lines[i].getColor();	//一番近い交点が更新されたら描画する線分の色を更新
			}
		}
	}
	return min_dist_cross;
}

void View::Draw(Vector playerPos, float playerAngle) {
	float left_angle = playerAngle - (float)M_PI_4;	//扇形の左端の角度
	float right_angle = playerAngle + (float)M_PI_4;//扇形の右端の角度
	int line_num = 0;//処理中の線が何本目なのかを保存

	//扇形の視野範囲を展開
	for (float angle = left_angle; angle < right_angle; angle += (float)M_PI_2 / RAY_NUM) {
		//視野の線分の終点を算出
		Vector end_pos = Vector(playerPos + Vector(cos(angle) * range, sin(angle) * range));
		Ray2 view_ray(playerPos, end_pos);	//視野判定の線分
		int color = Color::WHITE;			//描画時の色
		//最も近い交点を算出
		Vector min_dist_cross = CheckMinDistanceWall(view_ray, playerPos, color);

		//交点がないなら
		if (min_dist_cross.IsZero()) 
			min_dist_cross = end_pos;//終点はそのまま
		else {
			//Playerの視野の線分の描画処理
			DrawViewRenge(playerPos, min_dist_cross);

			Vector distance_vec = min_dist_cross - playerPos;
			float distance = distance_vec.getSize() * cos(angle - playerAngle);//上記のベクトルの長さ
			float view_height = Clump(14000.0f / distance, 0.0f, (float)HEIGHT_LIMIT);	//描画する線の長さ
			//一人称視点の描画処理
			DrawFPSView(line_num, color, view_height);
		}
		line_num++;
	}
}

void View::DrawViewRenge(Vector playerPos, Vector crossPos) {
	Ray2 sight(playerPos, crossPos);//視野の線分(始点,終点)
	//視野を線で描画
	DrawLine(sight.getBegin().getPosX(), sight.getBegin().getPosY(),//視点
				sight.getEnd().getPosX(), sight.getEnd().getPosY(),	//終点
				Color::WHITE);//線分の色
}

//1人称視点を描画
void View::DrawFPSView(int lineNum, int color, float viewHeight) {
	Vector view_root = Vector(50, 380);//描画線分の座標の基準
	Vector line_begin = view_root + Vector((float)(4 * lineNum), -viewHeight / 2.0f);//始点
	Vector line_end = line_begin + Vector(0.0f, viewHeight);//終点
	
	//線分の描画関数
	DrawLine(line_begin.getPosX(), line_begin.getPosY(), line_end.getPosX(), line_end.getPosY(), color);
}

void View::DrawNoise(bool isAddNoise) {
	//経過時間の計測
	timer += FPSController::Instance().getDeltaTime();
	//ノイズの個数を0～60に制限
	noise_num = Clump(noise_num, MIN_NOISE_NUM, MAX_NOISE_NUM);
	
	if (timer >= ADD_NOISE_INTERVAL) {
		if (isAddNoise)	
			noise_num++;
		else
			noise_num--;

		timer = 0;//経過時間をリセット
	}

	//増減した個数だけノイズを描画する
	for (int i = 0; i < noise_num; i++) {
		int pos_x = noise_pos[i].getPosX();//描画する座標のX成分を代入
		int pos_y = noise_pos[i].getPosY();//描画する座標のY成分を代入
		//指定の座標時黒い四角形を描画
		DrawBox(pos_x, pos_y, pos_x + width, pos_y + height, Color::BLOCK, TRUE);
		//上記の四角形を白線で囲む
		DrawLine(pos_x,			pos_y,			pos_x + width, pos_y,		   Color::WHITE);//上横線
		DrawLine(pos_x,			pos_y + height, pos_x,		   pos_y,		   Color::WHITE);//左縦線
		DrawLine(pos_x + width, pos_y,			pos_x + width, pos_y + height, Color::WHITE);//右縦線
		DrawLine(pos_x + width, pos_y + height, pos_x,		   pos_y + height, Color::WHITE);//下横線
	}
}
