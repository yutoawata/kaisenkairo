#include "Frame.h"

using namespace std;

//コンストラクタ
Frame::Frame(Vector setPosition, int setWidth, int setHeight, string setName) {
	position = setPosition;
	width = setWidth;
	height = setHeight;
	name = setName;
}

void Frame::Draw() {
	int pos_x = position.getPosX();
	int pos_y = position.getPosY();
	//フレームの名前を描画
	DrawString(pos_x, pos_y, (TCHAR*)name.c_str(), Color::WHITE);
	//四角形の枠線を描画
	DrawLine(pos_x,			pos_y,			pos_x + width, pos_y,		   Color::WHITE);//上横線
	DrawLine(pos_x,			pos_y,			pos_x,		   pos_y + height, Color::WHITE);//右縦線
	DrawLine(pos_x + width, pos_y,			pos_x + width, pos_y + height, Color::WHITE);//左縦線
	DrawLine(pos_x,			pos_y + height,	pos_x + width, pos_y + height, Color::WHITE);//下横線
}