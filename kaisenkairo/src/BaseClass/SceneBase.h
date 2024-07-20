#pragma once
#include "..\Text\GameText.h"

//�V�[���̊��N���X
class SceneBase {
public:
	//�Q�[���̏��
	enum class Type {
		NONE,
		TITLE,
		PLAY,
		CLEAR,
		GAMEOVER,
	};
protected:
	//�����o�ϐ�
	GameText* text = nullptr;	//�e�L�X�g�\���N���X
	Type next_type = Type::NONE;//�J�ڐ�̃V�[���̎��
	int font_size = 0;			//�t�H���g�T�C�Y
	float timer = 0;			//�o�ߎ���
	bool is_pause = false;		//�Q�[����~�t���O
	bool is_next = false;		//�V�[���J�ڃt���O

public:
	//�R���X�g���N�^
	SceneBase(int setFontSize) {
		font_size = setFontSize;
		SetFontSize(font_size);
	}

	//�f�X�g���N�^
	virtual ~SceneBase() {
		delete text;
	}

	//�A�N�Z�T
	//�J�ڐ�̃V�[���̎�ނ�Ԃ�
	inline Type getNextType() { return next_type; }
	//�J�ڃt���O��Ԃ�
	inline bool getIsNext() { return is_next; }	

	//�����o�֐�
	virtual void Update() = 0;	//�X�V����
	virtual void Draw() = 0;	//�`�揈��
};