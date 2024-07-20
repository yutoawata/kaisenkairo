#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include"DxLib.h"

class Vector {
private:
	//�����o�ϐ�
	float x = 0.0f;//���W��X����
	float y = 0.0f;//���W��Y����

public:
	//�R���X�g���N�^
	Vector() {}
	Vector(int setX, int setY);
	Vector(float setX, float setY);

	//���Z�q�I�[�o�[���[�h
	Vector operator +(const Vector& other);	//Vector�N���X���m�̉��Z��ǉ�4
	Vector operator -(const Vector& other);	//Vector�N���X���m�̌��Z��ǉ�
	Vector operator *(float value);			//�e�v�f�ւ̏�Z��ǉ�
	Vector operator /(float value);			//�e�v�f�ւ̏��Z��ǉ�
	Vector& operator +=(const Vector& other);
	Vector& operator -=(const Vector& other);
	bool operator ==(const Vector& other);	//Vector�N���X���m�̔�r��ǉ�
	operator VECTOR();//DX���C�u�����Ή��̃x�N�g���ւ̃L���X�g��ǉ�

	//�A�N�Z�T
	//DxLib�̕`��֐��ł͍��W������int�^�Ή��̈׃L���X�g���ēn��
	inline int getPosX() { return static_cast<int>(x); }
	inline int getPosY() { return static_cast<int>(y); }
	//X������Ԃ�
	inline float getX() { return x; }
	//Y������Ԃ�
	inline float getY() { return y; }

	//�����o�֐�
	//�����̃x�N�g���̒P�ʃx�N�g����Ԃ�
	static Vector Normalize(Vector mine);
	//�x�N�g���̒�����Ԃ�
	float getSize() { return (float)sqrt(x * x + y * y); }
	//�x�N�g����NULL�t���O��Ԃ�
	bool IsZero() { return x == 0 && y == 0; }
};