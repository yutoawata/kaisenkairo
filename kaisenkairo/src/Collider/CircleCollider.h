#pragma once
#include "..\BaseClass\ColliderBase.h"

//�~�̓����蔻��R���C�_�[�N���X
class CircleCollider : public ColliderBase {
private:
	//�����o�ϐ�
	int radius = 0;//���a

public:
	//�R���X�g���N�^
	CircleCollider(Vector setPos, int setRad, ObjectType setType);

	//�A�N�Z�T
	//���S���W��Ԃ�
	inline Vector getPosition() { return position; }
	//���a��Ԃ�
	inline int getRadius() { return radius; }

	//�����o�֐�
	//���W�̍X�V����
	void UpdatePosition(Vector newPos);
};