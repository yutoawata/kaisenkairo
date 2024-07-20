#include "FPSController.h"

const float FPSController::MAX_SECOND = 60.0f;

//�Ăяo������
FPSController& FPSController::Instance() {
	static FPSController instance;
	return instance;
}

//�X�V����
void FPSController::Update() {
	if (count == 0)
		//�~���b�P�ʂ̐��x�����J�E���^�̌��ݒl�𓾂�
		start_time = GetNowCount();
	if (count == MAX_FPS) {
		//�~���b�P�ʂ̐��x�����J�E���^�̌��ݒl�𓾂�
		int current_time = GetNowCount();
		//�t���[�����[�g���Z�o
		fps = 1000.f / ((current_time - start_time) /MAX_SECOND);
		count = 0;		//�J�E���g�����Z�b�g
		start_time = current_time;	//�J�n���Ԃ��X�V
	}
	count++;//1�b�Ԃ̃t���[�������J�E���g
}

//1/60�b�o�܂ŏ������ꎞ��~
void FPSController::Wait() {
	//�~���b�P�ʂ̐��x�����J�E���^�̌��ݒl�𓾂�
	int took_time = GetNowCount() - start_time;
	//�����̑ҋ@���Ԃ��Z�o
	int wait_time = count * 1000 / MAX_FPS - took_time;
	//�ҋ@���Ԃ�����Ȃ�
	if (wait_time > 0)
		//��������k�Ŏw�莞�Ԏ~�߂�
		Sleep(wait_time);
}