#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>
#include "DxLib.h"
#include "Ray2.h"

#define MAX 1.0f
#define MIN 0.0f
#define HALF_DEG 180

//第一引数に第二引数を連結する
void InsertLines(std::vector<Ray2>& lines, std::vector<Ray2> other);

//角度からベクトルを生成
Vector CreateVector(float angle, float size);

//交点の座標を算出
Vector Intersection(Ray2 ray1, Ray2 ray2);

//乱数生成関数
int CreateRandom(int min, int max);

//int型の値の上限と下限で制限する
int Clump(int value, int min, int max);

//float型の値の上限と下限で制限する
float Clump(float value, float min, float max);