#pragma once
#include "DxLib.h"
#include "..\Collider\CircleCollider.h"
#include "..\Collider\LineCollider.h"

//�����蔻�菈���N���X
class ColliderManager {
private:
	//�����o�ϐ�
	std::unordered_map<ObjectType, LineCollider*> line_colliders;//�����̓����蔻����z��
	std::vector<CircleCollider*> circle_colliders;	//�~�̓����蔻����z��
	CircleCollider* player_collider = nullptr;		//�v���C���[�̓����蔻����
	//�R���X�g���N�^
	ColliderManager();
	ColliderManager(const ColliderManager&) = delete;
public:
	//�f�X�g���N�^
	~ColliderManager();

	//�����o�֐�
	//���t�@�C���ł̌Ăяo���p�̊֐�
	static ColliderManager& Instance();
	//�e�R���C�_�̍X�V����
	void Update();	
	//�I�u�W�F�N�g�̉~�R���C�_��z��ɕۑ�
	void AddList(CircleCollider* collider);
	//�I�u�W�F�N�g�̐��R���C�_��z��ɕۑ�
	void AddList(LineCollider* collider);
	//�R���C�_�̓o�^�����N���A
	void ClearColliders();

private:
	//�~�Ɖ~�̏Փ˃t���O�̃`�F�b�N
	void UpdateFlag(CircleCollider* collider01, CircleCollider* collider02);
	//�~�Ɛ��̏Փ˃t���O�̃`�F�b�N
	void UpdateFlag(CircleCollider* cCollider, LineCollider* lCollider);
	//�~�Ɖ~�̓����蔻�菈��
	bool CheckCollision(CircleCollider& collider01, CircleCollider& collider02) const;
	//�~�Ɛ��̓����蔻��
	bool CheckCollision(CircleCollider& circleCollider, LineCollider& lineCollider) const;
};