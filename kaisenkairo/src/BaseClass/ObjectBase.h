#pragma once
#include <iostream>
#include "DxLib.h"
#include "..\Color\Color.h"
#include "..\Math\Vector.h"

//�ړ���O��Ƃ����I�u�W�F�N�g�̊��N���X
class ObjectBase {
protected:
	//�����o�ϐ�
	Vector position;//���S���W
	int color;		//�`�掞�̐F

public:
	//�R���X�g���N�^
	ObjectBase(Vector setPos, int setColor = Color::WHITE) {
		position = setPos;
		color = setColor;
	}

	//�f�X�g���N�^
	virtual ~ObjectBase() {}

	//�A�N�Z�T
	//�`�掞�̐F��Ԃ�
	inline int getColor() { return color; }
	
	//�����o�֐�
	virtual void Prepare() = 0;	//�X�V�O����
	virtual void Update() = 0;	//�X�V����
	virtual void Draw() = 0;	//�`�揈��
};