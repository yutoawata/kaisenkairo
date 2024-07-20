#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>
#include "DxLib.h"
#include "Ray2.h"

#define MAX 1.0f
#define MIN 0.0f
#define HALF_DEG 180

//�������ɑ�������A������
void InsertLines(std::vector<Ray2>& lines, std::vector<Ray2> other);

//�p�x����x�N�g���𐶐�
Vector CreateVector(float angle, float size);

//��_�̍��W���Z�o
Vector Intersection(Ray2 ray1, Ray2 ray2);

//���������֐�
int CreateRandom(int min, int max);

//int�^�̒l�̏���Ɖ����Ő�������
int Clump(int value, int min, int max);

//float�^�̒l�̏���Ɖ����Ő�������
float Clump(float value, float min, float max);