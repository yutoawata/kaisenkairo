#pragma once
#include "..\Color\Color.h"
#include <string>

//�e�L�X�g���N���X
class TextStatus {
private:
	//�����o�ϐ�
	std::string text;			//�e�L�X�g�̕�����
	int color = Color::WHITE;	//�����̐F
public:
	//�R���X�g���N�^
	TextStatus(std::string setText, int setColor);

	//�A�N�Z�T
	inline std::string getText() { return text; }//�������Ԃ�
	inline const char* getCharText() { return text.c_str(); }//�������const char*�^�ɃL���X�g���ĕԂ�
	inline int getColor() { return color; }	//������̐F��Ԃ�
};