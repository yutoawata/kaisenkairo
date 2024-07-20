#pragma once
#include "DxLib.h"
#include "..\ManagerClass\ColliderManager.h"
#include "..\BaseClass\ObjectBase.h"

//�G�΃I�u�W�F�N�g�N���X
class Enemy : public ObjectBase {
private:
	//�����o�ϐ�
	CircleCollider* collider = nullptr;	//�����蔻��
	Vector home_pos = Vector(0, 0);		//���W
	int radius = 15;	//�`�掞�̉~�̔��a
	float speed = 0.5f;	//�ړ����x

public:
	//�R���X�g���N�^
	Enemy(Vector setPos);

	//�f�X�g���N�^
	~Enemy();

	//�����o�֐�
	void Prepare() override;//�X�V�O����
	void Update() override;	//�X�V����
	void Draw() override;	//�`�揈��
private:
	void Move(Vector playerPos);	//�ړ�����
};
