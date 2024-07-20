#pragma once
#include "..\Math\Methods.h"
#include "..\Math\Vector.h"
#include <vector>

//�I�u�W�F�N�g�̎��
enum class ObjectType {
	PLAYER,		//�v���C���[
	ENEMY,		//�G�l�~�[
	WALL,		//��
	UP_EXIT,	//��o��
	DOWN_EXIT,	//���o��
	RIGHT_EXIT,	//�E�o��
	LEFT_EXIT,	//���o��
};

//�����蔻��̊�{���N���X
class ColliderBase {
protected:
	//�����o�ϐ�
	std::vector<ColliderBase> others;	//������������
	Vector position = Vector(0, 0);		//�I�u�W�F�N�g�̍��W
	ObjectType type;	//���g�̎��
	
public:
	//�R���X�g���N�^
	ColliderBase(Vector setPosition, ObjectType setType);

	//�f�X�g���N�^
	virtual ~ColliderBase();

	//�A�N�Z�T
	//������������̓����蔻�����Ԃ�
	inline std::vector<ColliderBase>& getOthers() { return others; }
	//�R���C�_�[�̍��W��Ԃ�
	inline Vector getPosition() { return position; }
	//���g�̎�ނ̃Q�b�^�[
	inline ObjectType getType() { return type; }
	
	//�����o�֐�
	//����̎�ށE�Փ˃t���O�̃��Z�b�g
	void Reset();
	//�Փ˂�������̎�ނ�ۑ��E�t���O��ON(�~�̓����蔻��)
	void UpdateFlag(const ColliderBase& other);
};