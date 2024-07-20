#include "LineCollider.h"

//�R���X�g���N�^
LineCollider::LineCollider(std::vector<Ray2> setLines, Vector setPos, ObjectType setType)
	: ColliderBase(setPos, setType) {
	lines = setLines;
}

LineCollider::~LineCollider() {}

//���W�̍X�V����
void LineCollider::UpdateLines(std::vector<Ray2> newLines) {
	lines = newLines;
}