#pragma once
#include "..\BaseClass\SceneBase.h"

//�^�C�g���V�[���N���X
class TitleScene : public SceneBase {
private:
	//�����o�ϐ�
	std::vector<std::string> texts = {//�^�C�g���e�L�X�g
		"         �����L",
		"����������i�݁A���[�v���甲���o��",
		"	Input Space to Start Game"
	};
public:
	//�R���X�g���N�^
	TitleScene(int fontSize = 100);

	//�����o�֐�
	void Update() override;	//�X�V����
	void Draw() override;	//�`�揈��
};