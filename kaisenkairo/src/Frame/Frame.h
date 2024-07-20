#pragma once
#include <string>
#include "DxLib.h"
#include "..\Color\Color.h"
#include "..\Math\Vector.h"

//�g���N���X
class Frame {
private:
	//�����o�ϐ�
	std::string name = "";			//�g���̖��O
	Vector position = Vector(0, 0);	//�g���̍���̍��W
	int width = 0;	//����
	int height = 0;	//�c��
public:
	//�R���X�g���N�^
	Frame(Vector setPosition, int setWidth, int setHeight, std::string setName = "");

	//�����o�֐�
	//�`�揈��
	void Draw();
};