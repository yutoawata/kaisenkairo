#pragma once
#include "..\Frame\Frame.h"
#include "..\BaseClass\SceneBase.h"
#include "..\ManagerClass\ColliderManager.h"
#include "..\ManagerClass\MapManager.h"
#include "..\ManagerClass\ObjectManager.h"
#include "..\Color\Color.h"

//�Q�[���v���C�V�[��
class PlayScene : public SceneBase {
private:
	//�����o�ϐ�
	std::vector<std::string> texts = {//��������e�L�X�g
		"�ڕW:���������ɐF������!!",
		"",
		"�ړ�:W�L�[(�O����)�ES�L�[(�����)",
		"     A�L�[(������)�ED�L�[(�E����)",
		"���_�ړ�:�}�E�X",
		"�Q�[���I��:ESC�L�["
		
	};
	Frame* view_frame = new Frame(Vector(50.0f, 30.0f), 1200, 700);
	Frame* text_frame_01 = new Frame(Vector(50.0f, 800.0f), 850, 280, "���O");
	Frame* text_frame_02 = new Frame(Vector(960.0f, 800.0f), 850, 280, "�������");
public:
	//�R���X�g���N�^
	PlayScene(int fontSize = 32);

	//�f�X�g���N�^
	~PlayScene();

	//�����o�֐�
	//�X�V����
	void Update() override;
	//�`�揈��
	void Draw() override;
private:
	//�Q�[�����U���g�`�F�b�N
	void CheckResult();
};