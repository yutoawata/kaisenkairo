#include "Methods.h"

using namespace std;

//角度からベクトルを生成する
Vector CreateVector(float angle, float size) {
	return Vector(cos(angle) * size, sin(angle) * size);
}

//配列を結合する
void InsertLines(vector<Ray2>& lines, vector<Ray2> other) {
	for (int i = 0; i < other.size(); i++) {
		lines.push_back(other[i]);
	}
}

//交点判定・取得
 Vector Intersection(Ray2 ray_01, Ray2 ray_02) {
	//各線分の始点終点を代入
	Vector ray_01_begin = Vector(ray_01.getBegin().getX(), ray_01.getBegin().getY());
	Vector ray_01_end = Vector(ray_01.getEnd().getX(), ray_01.getEnd().getY());
	Vector ray_02_begin = Vector(ray_02.getBegin().getX(), ray_02.getBegin().getY());
	Vector ray_02_end = Vector(ray_02.getEnd().getX(), ray_02.getEnd().getY());

	//交点を計算
	//外積
	float cross = (ray_01_end.getX() - ray_01_begin.getX()) * (ray_02_end.getY() - ray_02_begin.getY())
		- (ray_01_end.getY() - ray_01_begin.getY()) * (ray_02_end.getX() - ray_02_begin.getX());

	//外積した値が0なら
	if (cross == 0.0f)
		return Vector(NULL, NULL);//交点がないため、NULLを返す

	float ray_01_x_delta = ray_01_end.getX() - ray_01_begin.getX();
	float ray_01_y_delta = ray_01_end.getY() - ray_01_begin.getY();

	//媒介変数を計算
	float t1 = ((ray_02_end.getY() - ray_02_begin.getY()) * (ray_02_begin.getX() - ray_01_begin.getX())
		- (ray_02_end.getX() - ray_02_begin.getX()) * (ray_02_begin.getY() - ray_01_begin.getY())) / cross;

	float t2 = ((ray_01_end.getY() - ray_01_begin.getY()) * (ray_01_begin.getX() - ray_02_begin.getX()) - (ray_01_end.getX()
		- ray_01_begin.getX()) * (ray_01_begin.getY() - ray_02_begin.getY())) / cross;

	//交差判定
	//媒介変数それぞれが　1より小さい　かつ　正の値であるなら
	if(t1 >= MIN && t1 <= MAX && t2 >= MIN && t2 <= MAX) {
		//交差しているので座標を返す
		return Vector(ray_01_begin.getX() + t1 * ray_01_x_delta, ray_01_begin.getY() + t1 * ray_01_y_delta);
	}
	else {
		//交差してないので、NULLを返す
		return Vector(0, 0);
	}
}

//乱数生成関数(int型)
int CreateRandom(int min, int max) {
	random_device rd;

	mt19937 engine(rd());

	uniform_int_distribution<int> dist(min, max);

	int result = dist(engine);
	return result;
}

//int型の値の下限と上限を制限
int Clump(int value, int min, int max) {
	//値の下限をminに制限
	if (value < min) {
		return min;
	}
	//値の上限をmaxに制限
	else if (value > max) {
		return max;
	}
	//限界値を超えてなければそのままの値を返す
	else {
		return value;
	}
}

//float型の値の下限と上限を制限
float Clump(float value, float min, float max)
{
	//値の下限をminに制限
	if (value < min) {
		return min;
	}
	//値の上限をmaxに制限
	else if (value > max) {
		return max;
	}
	//限界値を超えてなければそのままの値を返す
	else {
		return value;
	}
}