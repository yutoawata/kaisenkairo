#include "ExitBase.h"

//�R���X�g���N�^
ExitBase::ExitBase(int exitMapId, int setColor) {
	next_map_id = exitMapId;
	color = setColor;
}

//�f�X�g���N�^
ExitBase::~ExitBase() {
	delete collider;
}

//�X�V����
void ExitBase::Prepare() {
	collider->Reset();//�����蔻��������Z�b�g
}

//�`�揈��
void ExitBase::Draw() {
	//�R�̎��^�ŕ`��
	for (int i = 0; i < lines.size(); i++) {
		DrawLine(lines[i].getBegin().getPosX(), lines[i].getBegin().getPosY(),	//�n�_���W
				 lines[i].getEnd().getPosX(),	lines[i].getEnd().getPosY(),	//�I�_���W
				 Color::WHITE//������\������ۂ̐F
		);
	}
}

//�v���C���[�������Ă������̔��菈��
bool ExitBase::CheckEnter() {
	for (ColliderBase& other : collider->getOthers()) {
		//�v���C���[�ƏՓ˂��Ă���Ȃ�
		if (other.getType() == ObjectType::PLAYER) {
			return true;
		}
	}
	return false;
}

ObjectType ExitBase::GetEnterType(ObjectType exitType) {
	switch (exitType) {
	case ObjectType::UP_EXIT:
		return ObjectType::DOWN_EXIT;
		break;
	case ObjectType::DOWN_EXIT:
		return ObjectType::UP_EXIT;
		break;
	case ObjectType::RIGHT_EXIT:
		return ObjectType::LEFT_EXIT;
		break;
	case ObjectType::LEFT_EXIT:
		return ObjectType::RIGHT_EXIT;
		break;
	default:
		throw std::invalid_argument("������ ObjectType ���n����܂���"); // ��O���X���[;
		break;
	}
}