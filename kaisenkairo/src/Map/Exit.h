#pragma once
#include "DxLib.h"
#include "..\BaseClass\ExitBase.h"
#include "..\Collider\LineCollider.h"

//��Ɍ������ׂ̏o����
class UpExit : public ExitBase {
public:
	//�R���X�g���N�^
	UpExit(Vector root, int exitStageId, int setColor);
};

////////////////////////////////////////////////////////////////////////////////////////

//���Ɍ������ׂ̏o����
class DownExit :public ExitBase {
public:
	//�R���X�g���N�^
	DownExit(Vector root, int exitStageId, int setColor);
};

////////////////////////////////////////////////////////////////////////////////////////

//�E�Ɍ������ׂ̏o����
class RightExit :public ExitBase {
public:
	//�R���X�g���N�^
	RightExit(Vector root, int exitStageId, int setColor);
};

////////////////////////////////////////////////////////////////////////////////////////

//���Ɍ������ׂ̏o����
class LeftExit :public ExitBase {
public:
	//�R���X�g���N�^
	LeftExit(Vector root, int exitStageId, int setColor);
};
