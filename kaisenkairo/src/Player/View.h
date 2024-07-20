#pragma once
#include "DxLib.h"
#include "..\GameSystem\FPSController.h"
#include "..\ManagerClass\mapmanager.h"
#include "..\Math\Methods.h"

//���E�`��N���X
class View {
private:
	//�����o�萔
	static const int MAX_NOISE_NUM = 100;//�`�悷��m�C�Y�̍ő�l(�z��̗v�f���V�e�C�Ɏg�p���邽��static�萔�ɂ���)
	const int MIN_NOISE_NUM = 0;		//�`�悷��m�C�Y�̍ŏ��l
	const int RAY_NUM = 300;			//�`��Ɏg�p��������̖{��
	const int HEIGHT_LIMIT = 700;		//�`�悷�鍂���̌��E
	const int MIN_X = 50;
	const int MIN_Y = 30;
	const float ADD_NOISE_INTERVAL = 0.2f;

	//�����o�ϐ�
	Vector noise_pos[MAX_NOISE_NUM] = {};//�m�C�Y��`�悷����W
	Vector min_pos = Vector(50, 30);//�m�C�Y�̍��W�̐����̉���
	Vector max_pos = Vector(1250.0f - width, 730.0f - height);//�m�C�Y�̍��W�̐����̏��
	int noise_num = 0;		//�m�C�Y�̌��J�E���^�[
	int range = 700;		//����̋���
	int width = 100;		//�m�C�Y�̉���
	int height = 60;		//�m�C�Y�̏c��
	int min_x = 50;
	int min_y = 30;
	int max_x = 1250 - width;
	int max_y = 730 - height;
	float timer = 0;		//�m�C�Y�`�掞�̌o�ߎ���

public:
	//�R���X�g���N�^
	View();

	//�����o�֐�
	//�`�揈��
	void Draw(Vector playerPos, float playerAngle);
	//�_���[�W���󂯂Ă����̂̈֎q��`��
	void DrawNoise(bool isAddNoise);
private:
	//�v���C���̎��E���}�b�v�ɕ`��
	void DrawViewRenge(Vector playerPos, Vector crossPos);
	//��l�̎��_��`��
	void DrawFPSView(int lineNum, int lineColor, float viewHeight);
	//�ǂ̉��������Ȃ��悤�ɂɃv���C���[�̎������ԋ߂���_��T��
	Vector CheckMinDistanceWall(Ray2 ray, Vector playerpos, int& color);
};