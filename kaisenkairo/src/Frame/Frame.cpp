#include "Frame.h"

using namespace std;

//�R���X�g���N�^
Frame::Frame(Vector setPosition, int setWidth, int setHeight, string setName) {
	position = setPosition;
	width = setWidth;
	height = setHeight;
	name = setName;
}

void Frame::Draw() {
	int pos_x = position.getPosX();
	int pos_y = position.getPosY();
	//�t���[���̖��O��`��
	DrawString(pos_x, pos_y, (TCHAR*)name.c_str(), Color::WHITE);
	//�l�p�`�̘g����`��
	DrawLine(pos_x,			pos_y,			pos_x + width, pos_y,		   Color::WHITE);//�㉡��
	DrawLine(pos_x,			pos_y,			pos_x,		   pos_y + height, Color::WHITE);//�E�c��
	DrawLine(pos_x + width, pos_y,			pos_x + width, pos_y + height, Color::WHITE);//���c��
	DrawLine(pos_x,			pos_y + height,	pos_x + width, pos_y + height, Color::WHITE);//������
}