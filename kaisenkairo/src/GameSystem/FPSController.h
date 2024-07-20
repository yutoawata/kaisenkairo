#pragma once
#include "DxLib.h"

class FPSController {
private:
	//�����o�ϐ�
	static const int MAX_FPS = 60;	//�t���[�����[�g�̍ő�l
	static const float MAX_SECOND;	//1���Ԃł̍ő�b��
	int start_time = 0;	//�v���J�n���̎���
	int count = 0;		//�t���[�����̃J�E���^�[
	float fps = 0;		//�t���[�����[�g

	//�R���X�g���N�^
	FPSController() {}
	FPSController(const FPSController& ) = delete;

public:
	//�Ăяo������
	static FPSController& Instance();

	//�A�N�Z�T
	inline float getDeltaTime() { return 1 / fps; }	//1�t���[���Ōo�߂�������

	//�����o�֐�
	//�X�V����
	void Update();
	//1/60�b�o�܂ŏ������ꎞ��~
	void Wait();
};