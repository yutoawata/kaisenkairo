#include "PlayScene.h"

//�R���X�g���N�^
PlayScene::PlayScene(int fontSize)
	:SceneBase(fontSize) {
	font_size = fontSize;
	next_type = Type::CLEAR;
	text = new GameText(Vector(960, 840), texts, Color::YELLOW, font_size);
	MapManager::Instance().SetUpMap();
	ObjectManager::Instance().EntryPlayer(font_size);
	ObjectManager::Instance().EntryEnemy();
}

//�f�X�g���N�^
PlayScene::~PlayScene() {
	delete view_frame;
	delete text_frame_01;
	delete text_frame_02;
}

//�X�V����
void PlayScene::Update() {
	//�e�Ǘ��N���X�̍X�V�O�������s��
	ObjectManager::Instance().Prepare();
	MapManager::Instance().Prepare();

	//�e�Ǘ��N���X�̍X�V�������s��
	ColliderManager::Instance().Update();
	MapManager::Instance().Update();
	ObjectManager::Instance().Update();

	CheckResult();
}

//�`�揈��
void PlayScene::Draw() {
	//�}�b�v�Ǘ��N���X�̕`�揈�����s��
	MapManager::Instance().Draw();
	//�J�b�g�C����ԂłȂ��Ȃ�
	if (!MapManager::Instance().getIsCutin()) {
		//�I�u�W�F�N�g�Ǘ��N���X�̕`�揈�����s��
		ObjectManager::Instance().Draw();
		text->Draw();
		view_frame->Draw();
		text_frame_01->Draw();
		text_frame_02->Draw();
	}
}

//�Q�[���v���C���ʂ̃`�F�b�N
void PlayScene::CheckResult() {
	//�Q�[���̂�ጋ�ʂ��擾
	ObjectManager::ResultStatus result = ObjectManager::Instance().CheckResult(MapManager::Instance().getIntStageNum());
	switch (result) {
	case ObjectManager::ResultStatus::PLAY://�Q�[�����Ȃ�
		//���������ɏ����𔲂���
		break;
	case ObjectManager::ResultStatus::CLEAR://�Q�[���N���A�Ȃ�
		next_type = Type::CLEAR;//�J�ڌ�̃V�[���̎�ނɃN���A����
		is_next = true;			//�J�ڃt���O��true�ɂ���
		break;
	case ObjectManager::ResultStatus::GAME_OVER://�Q�[���I�[�o�[�Ȃ�
		next_type = Type::GAMEOVER;	//�J�ڐ�̃V�[���̎�ނɃQ�[���I�[�o�[����
		is_next = true;				//�J�ڃt���O��true�ɂ���
		break;
	}
}