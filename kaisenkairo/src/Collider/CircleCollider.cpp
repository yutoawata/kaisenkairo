#include "CircleCollider.h"

//�R���X�g���N�^
CircleCollider::CircleCollider(Vector setPos, int setRad, ObjectType setType)
	: ColliderBase(setPos, setType) {
	radius = setRad;
}

//���W�̍X�V����
void CircleCollider::UpdatePosition(Vector newPos) {
	position = newPos;
}