#pragma once
#include "..\Color\Color.h"
#include "Vector.h"

//�����N���X
class Ray2 {
private:
	//�����o�ϐ�
	Vector begin = Vector(0, 0);//�n�_���W
	Vector end = Vector(0, 0);	//�I�_���W
	int color = Color::WHITE;	//�����̐F

public:
	//�R���X�g���N�^
	Ray2();
	Ray2(Vector setBegin, Vector setEnd, int setColor = Color::WHITE);

	//�A�N�Z�T
	//�n�_��n��
	inline Vector getBegin() { return begin; }
	//�I�_��n��
	inline Vector getEnd() { return end; }
	//�����̐F��n��
	inline int getColor() { return color; }
};