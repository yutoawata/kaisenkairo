#include "Methods.h"

using namespace std;

//�p�x����x�N�g���𐶐�����
Vector CreateVector(float angle, float size) {
	return Vector(cos(angle) * size, sin(angle) * size);
}

//�z�����������
void InsertLines(vector<Ray2>& lines, vector<Ray2> other) {
	for (int i = 0; i < other.size(); i++) {
		lines.push_back(other[i]);
	}
}

//��_����E�擾
 Vector Intersection(Ray2 ray_01, Ray2 ray_02) {
	//�e�����̎n�_�I�_����
	Vector ray_01_begin = Vector(ray_01.getBegin().getX(), ray_01.getBegin().getY());
	Vector ray_01_end = Vector(ray_01.getEnd().getX(), ray_01.getEnd().getY());
	Vector ray_02_begin = Vector(ray_02.getBegin().getX(), ray_02.getBegin().getY());
	Vector ray_02_end = Vector(ray_02.getEnd().getX(), ray_02.getEnd().getY());

	//��_���v�Z
	//�O��
	float cross = (ray_01_end.getX() - ray_01_begin.getX()) * (ray_02_end.getY() - ray_02_begin.getY())
		- (ray_01_end.getY() - ray_01_begin.getY()) * (ray_02_end.getX() - ray_02_begin.getX());

	//�O�ς����l��0�Ȃ�
	if (cross == 0.0f)
		return Vector(NULL, NULL);//��_���Ȃ����߁ANULL��Ԃ�

	float ray_01_x_delta = ray_01_end.getX() - ray_01_begin.getX();
	float ray_01_y_delta = ray_01_end.getY() - ray_01_begin.getY();

	//�}��ϐ����v�Z
	float t1 = ((ray_02_end.getY() - ray_02_begin.getY()) * (ray_02_begin.getX() - ray_01_begin.getX())
		- (ray_02_end.getX() - ray_02_begin.getX()) * (ray_02_begin.getY() - ray_01_begin.getY())) / cross;

	float t2 = ((ray_01_end.getY() - ray_01_begin.getY()) * (ray_01_begin.getX() - ray_02_begin.getX()) - (ray_01_end.getX()
		- ray_01_begin.getX()) * (ray_01_begin.getY() - ray_02_begin.getY())) / cross;

	//��������
	//�}��ϐ����ꂼ�ꂪ�@1��菬�����@���@���̒l�ł���Ȃ�
	if(t1 >= MIN && t1 <= MAX && t2 >= MIN && t2 <= MAX) {
		//�������Ă���̂ō��W��Ԃ�
		return Vector(ray_01_begin.getX() + t1 * ray_01_x_delta, ray_01_begin.getY() + t1 * ray_01_y_delta);
	}
	else {
		//�������ĂȂ��̂ŁANULL��Ԃ�
		return Vector(0, 0);
	}
}

//���������֐�(int�^)
int CreateRandom(int min, int max) {
	random_device rd;

	mt19937 engine(rd());

	uniform_int_distribution<int> dist(min, max);

	int result = dist(engine);
	return result;
}

//int�^�̒l�̉����Ə���𐧌�
int Clump(int value, int min, int max) {
	//�l�̉�����min�ɐ���
	if (value < min) {
		return min;
	}
	//�l�̏����max�ɐ���
	else if (value > max) {
		return max;
	}
	//���E�l�𒴂��ĂȂ���΂��̂܂܂̒l��Ԃ�
	else {
		return value;
	}
}

//float�^�̒l�̉����Ə���𐧌�
float Clump(float value, float min, float max)
{
	//�l�̉�����min�ɐ���
	if (value < min) {
		return min;
	}
	//�l�̏����max�ɐ���
	else if (value > max) {
		return max;
	}
	//���E�l�𒴂��ĂȂ���΂��̂܂܂̒l��Ԃ�
	else {
		return value;
	}
}