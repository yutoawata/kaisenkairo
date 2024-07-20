#include "ColliderBase.h"

//�R���X�g���N�^
ColliderBase::ColliderBase(Vector setPosition, ObjectType setType) {
	position = setPosition;
	type = setType;
}

//�f�X�g���N�^
ColliderBase::~ColliderBase() {}

//�~�̓����蔻��̌��ʏ�L����
void ColliderBase::UpdateFlag(const ColliderBase& other) {
	others.emplace_back(other);	//������������̃R���C�_�[��ۑ�
}

//���Z�b�g����
void ColliderBase::Reset() {
	others.clear();//Collider�������Z�b�g
}
