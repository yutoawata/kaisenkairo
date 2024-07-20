#include "ResultScene.h"

const std::vector<std::string> ResultScene::clear_texts = {
		"        �ʐM����",
		"	�ڂ̒[���ɂ��ǂ蒅����",
		"�G���^�[�L�[�Ń^�C�g���ɖ߂�"
};

const std::vector<std::string> ResultScene::gameover_texts = {
	"        �ʐM���s",
	"	�@	�d�g���r�؂ꂽ",
	"�G���^�[�L�[�Ń^�C�g���ɖ߂�"
};

ResultScene::ResultScene(int fontSize)
	: SceneBase(fontSize) {
	
}

void ResultScene::Update() {
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		is_next = true;
	}
}

void ResultScene::Draw() {
	text->Draw();//�e�L�X�g�`�揈��
}


//�X�V����
void ClearScene::Update() {
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		is_next = true;
	}
}

//�`�揈��
void ClearScene::Draw() {
	text->Draw();//�e�L�X�g�`�揈��
}
//////////////////////////////////////////////////////////////////////

//�X�V����
void GameOverScene::Update() {
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		is_next = true;
	}
}

//�`�揈��
void GameOverScene::Draw() {
	text->Draw();//�e�L�X�g�`�揈��
}