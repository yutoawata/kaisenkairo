#pragma once
#include "..\BaseClass\SceneBase.h"

class ResultScene : public SceneBase {
private:
	static const std::vector<std::string> clear_texts;
	static const std::vector<std::string> gameover_texts;
public:
	ResultScene(int fontSize = 120);

	void Update() override;
	void Draw() override;
};

class ClearScene : public SceneBase {
private:
	//�����o�ϐ�
	std::vector<std::string> texts = {//�N���A�e�L�X�g
		"        �ʐM����",
		"	�ڂ̒[���ɂ��ǂ蒅����",
		"�G���^�[�L�[�Ń^�C�g���ɖ߂�"
	};
public:
	//�R���X�g���N�^
	ClearScene(int fontSize = 120)
		:SceneBase(fontSize) {
		next_type = Type::TITLE;
		text = new GameText(Vector(200, 400), texts, Color::WHITE, font_size);
	}

	//�����o�֐�
	//�X�V����
	void Update() override;
	//�`�揈��
	void Draw() override;
};

class GameOverScene : public SceneBase {
private:
	//�����o�ϐ�
	std::vector<std::string> texts = {//�N���A�e�L�X�g
		"        �ʐM���s",
		"	�@	�d�g���r�؂ꂽ",
		"�G���^�[�L�[�Ń^�C�g���ɖ߂�"
	};
public:
	//�R���X�g���N�^
	GameOverScene(int fontSize = 120)
		:SceneBase(fontSize) {
		next_type = Type::TITLE;
		text = new GameText(Vector(200, 400), texts, Color::WHITE, font_size);
	}

	//�����o�֐�
	//�X�V����
	void Update() override;
	//�`�揈��
	void Draw() override;

};