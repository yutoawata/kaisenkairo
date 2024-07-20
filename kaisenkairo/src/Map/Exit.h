#pragma once
#include "DxLib.h"
#include "..\BaseClass\ExitBase.h"
#include "..\Collider\LineCollider.h"

//上に向かう為の出入口
class UpExit : public ExitBase {
public:
	//コンストラクタ
	UpExit(Vector root, int exitStageId, int setColor);
};

////////////////////////////////////////////////////////////////////////////////////////

//下に向かう為の出入口
class DownExit :public ExitBase {
public:
	//コンストラクタ
	DownExit(Vector root, int exitStageId, int setColor);
};

////////////////////////////////////////////////////////////////////////////////////////

//右に向かう為の出入口
class RightExit :public ExitBase {
public:
	//コンストラクタ
	RightExit(Vector root, int exitStageId, int setColor);
};

////////////////////////////////////////////////////////////////////////////////////////

//左に向かう為の出入口
class LeftExit :public ExitBase {
public:
	//コンストラクタ
	LeftExit(Vector root, int exitStageId, int setColor);
};
