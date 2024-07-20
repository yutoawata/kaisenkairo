#include "DxLib.h"
#include "GameMaster.h"

//�R���X�g���N�^
GameMaster::GameMaster() {
	//�Q�[���̉𑜓x�ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR);
	//�Q�[�����t���X�N���[���ɐݒ�
	ChangeWindowMode(FALSE);
	//���C�u�����J�n
	is_init = static_cast<bool>(DxLib_Init());
	//�}�E�X�J�[�\���̕\����OFF
	SetMouseDispFlag(FALSE);
	//�`��̈�̐ݒ�
	SetDrawScreen(DX_SCREEN_BACK);
	//�Q�[���J�n���̃V�[����ݒ�
	ChangeScene(SceneBase::Type::TITLE);
}

//�f�X�g���N�^
GameMaster::~GameMaster() {
	delete current_scene;
	DxLib_End();
}

//�V�[���J�ڏ���
void GameMaster::ChangeScene(SceneBase::Type nextScene) {
	
	delete current_scene;//�J�ڑO�̃V�[�����폜

	switch (nextScene) {
	case SceneBase::Type::TITLE:
		current_scene = new TitleScene();//�^�C�g���ɑJ��
		break;
	case SceneBase::Type::PLAY:
		current_scene = new PlayScene();//�Q�[���v���C�V�[���ɑJ��
		break;
	case SceneBase::Type::CLEAR:
		current_scene = new ClearScene();//�N���A�V�[���N���X�ɑJ��
		break;
	case SceneBase::Type::GAMEOVER:
		current_scene = new GameOverScene();//�Q�[���I�[�o�[�V�[���ɑJ��
		break;
	default:
		is_init = false;//�듮��̈׃Q�[�����I��
		break;
	}
}

void GameMaster::Update() {
	//���݂̃V�[�����Ȃ��@�܂��́@�J�ڃt���O��ture�Ȃ�
	if (current_scene == nullptr || current_scene->getIsNext())
		ChangeScene(current_scene->getNextType());//�J�ڏ��������s

	current_scene->Update();
	//�}�E�X�J�[�\���̍��W�𒆐S�ɖ߂�
	SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

//��ʂ̘g��`��
void GameMaster::Draw() {
	//���݂̃V�[���̕`�揈��
	current_scene->Draw();
}

//�Q�[�����[�v����
void GameMaster::Run() {
	while (!ProcessMessage() && !is_init) {

		ClearDrawScreen();
		Update();
		Draw();

		//Escape�L�[�ŃQ�[���������I��
		if (CheckHitKey(KEY_INPUT_ESCAPE)) 
			break;
		
		FPSController::Instance().Update();

		ScreenFlip();//�t���b�v�֐�

		FPSController::Instance().Wait();
	}
}