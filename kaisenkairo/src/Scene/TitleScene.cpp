#include "TitleScene.h"

//�R���X�g���N�^
TitleScene::TitleScene(int fontSize)
	:SceneBase(fontSize) {
	next_type = Type::PLAY;
	text = new GameText(Vector(200, 400), texts, Color::WHITE, font_size);
}

//�X�V����
void TitleScene::Update() {
	if (CheckHitKey(KEY_INPUT_SPACE))
		is_next = true;//�J�ڃt���O��true�ɂ���
}

//�`�揈��
void TitleScene::Draw() {
	text->Draw();//�e�L�X�g�`�揈��
}