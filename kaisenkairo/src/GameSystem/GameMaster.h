#pragma once
#include "DxLib.h"
#include "..\Color\Color.h"
#include "..\GameSystem\FPSController.h"
#include "..\Scene\TitleScene.h"
#include "..\Scene\PlayScene.h"
#include "..\Scene\ResultScene.h"

//�Q�[���̃��C�����[�v���s���N���X
class GameMaster {
private:
	//�����o�萔
	const int SCREEN_WIDTH = 1920;	//�Q�[���E�B���h�E�̉���
	const int SCREEN_HEIGHT = 1080;	//�Q�[���E�B���h�E�̏c��
	const int SCREEN_COLOR = 32;	//�Q�[���E�B���h�E�̃J���[�r�b�g��

	//�����o�ϐ�
	SceneBase* current_scene = nullptr;//�e�V�[�����Ƃ̏���������N���X
	bool is_init = false;
public:
	//�R���X�g���N�^
	GameMaster();

	//�f�X�g���N�^
	~GameMaster();

	//�����o�֐�
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
	//���C�����[�v����
	void Run();
	//�V�[���J�ڏ���
	void ChangeScene(SceneBase::Type nextStatus);
};