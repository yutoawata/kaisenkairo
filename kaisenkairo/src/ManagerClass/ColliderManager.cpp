#include "ColliderManager.h"

ColliderManager::ColliderManager() {}

ColliderManager::~ColliderManager() {}

//�ۑ������R���C�_�����폜
void ColliderManager::ClearColliders() {
	circle_colliders.clear();
	line_colliders.clear();
}

//���t�@�C���ł̌Ăяo���p�̊֐�
ColliderManager& ColliderManager::Instance() {
	static ColliderManager instance;
	return instance;
}

//�����蔻�菈��������Collider�̃��X�g�ɒǉ�
void ColliderManager::AddList(CircleCollider* collider) {
	if (collider->getType() == ObjectType::PLAYER) {
		player_collider = collider;
	}
	else {
		circle_colliders.emplace_back(collider);
	}
}

//�����蔻�菈��������Collider�̃��X�g�ɒǉ�
void ColliderManager::AddList(LineCollider* collider) {
	line_colliders[collider->getType()] = collider;
}

void ColliderManager::Update() {
	//�����Ƃ̓����蔻��
	for (auto& line_collider : line_colliders) {
		UpdateFlag(player_collider, line_collider.second);
	}
	//�G�l�~�[�̓����蔻��
	for (int i = 0; i < circle_colliders.size(); i++) {
		UpdateFlag(player_collider, circle_colliders[i]);
	}
}

//�~�Ɖ~�̓����蔻����̍X�V����
void ColliderManager::UpdateFlag(CircleCollider* collider01, CircleCollider* collider02) {
	if (CheckCollision(*collider01, *collider02)) {
		//�����蔻�茋�ʂ��X�V
		collider01->UpdateFlag(*collider02);
		collider02->UpdateFlag(*collider01);
	}
}

//�~�Ɛ��̓����蔻����̍X�V����
void ColliderManager::UpdateFlag(CircleCollider* cCollider, LineCollider* lCollider) {
	if (CheckCollision(*cCollider, *lCollider)) {
		//�~�̓����蔻�茋�ʂ��X�V
		cCollider->UpdateFlag(*lCollider);
		//�����̓����蔻�茋�ʂ��X�V
		lCollider->UpdateFlag(*cCollider);
	}
}

//�~�Ɖ~�̓����蔻��
bool ColliderManager::CheckCollision(CircleCollider& collider01, CircleCollider& collider02) const {
	//collider02�̒��S���W=>collider01�̒��S���W�̃x�N�g���𐶐�
	VECTOR distance_vec = VSub(collider01.getPosition(), collider02.getPosition());
	float distance_magnitude = VSize(distance_vec);//�x�N�g���̑傫�����狗�������߂�

	//��̉~�̔��a�̘a��苗�����߂���ΏՓ˂��Ă���
	if (distance_magnitude < collider01.getRadius() + collider02.getRadius())
		return true;

	return false;
}

//�~�Ɛ��̓����蔻��
bool ColliderManager::CheckCollision(CircleCollider& circleCollider, LineCollider& lineCollider) const {

	int circle_radius = circleCollider.getRadius();//�~�̔��a���擾
	for (int i = 0; i < lineCollider.getLines().size(); i++) {
		Ray2 line = lineCollider.getLines()[i];//�����̓����蔻�����z�񂩂璊�o
		Vector begin_to_center = circleCollider.getPosition() - line.getBegin();//�����̎n�_=>�~�̒��S�̃x�N�g���𐶐�
		Vector end_to_centor = circleCollider.getPosition() - line.getEnd();	//�����̏I�_=>�~�̒��S�̃x�N�g���𐶐�
		Vector begin_to_end = line.getEnd() - line.getBegin();//�����̃x�N�g���𐶐�

		Vector normal_begin_to_end = Vector::Normalize(begin_to_end);		//�����̃x�N�g���𐳋K��
		Vector normal_begin_to_center = Vector::Normalize(begin_to_center);	//�����̎n�_=>�~�̒��S�̃x�N�g���𐳋K��
		//�O�όv�Z
		float cross = normal_begin_to_end.getX() * begin_to_center.getY() - normal_begin_to_end.getY() * begin_to_center.getX();

		//��Βl�Ƃ��Ĉ����������߁A���̒l�Ȃ琳�̒l�Ƃ��ĕԂ�
		cross = cross < 0 ? -cross : cross;

		//�O�ς̒l�����a�̒l�ȏ�̂Ƃ��A�Փ˂��ĂȂ��̂Ŏ��̃��[�v�ɍs��
		if (cross >= circle_radius) continue;

		float dot_01 = begin_to_center.getX() * begin_to_end.getX() + begin_to_center.getY() * begin_to_end.getY();
		float dot_02 = end_to_centor.getX() * begin_to_end.getX() + end_to_centor.getY() * begin_to_end.getY();

		//�n�_=>�~�̓��ςƏI�_=>�~�̓��ς��|�����l��0�ȉ��̂Ȃ�A�Փ˂��Ă���
		if (dot_01 * dot_02 <= 0) return true;

		//�n�_=>�~�̃x�N�g���̒����ƏI�_=>�~�̃x�N�g���̒����̂ǂ��炩���~�̔��a�ȏ�̂Ȃ�
		if (VSize(begin_to_center) > circle_radius || VSize(end_to_centor) > circle_radius)
			continue;//�d�Ȃ��Ă��Ȃ��̂Ŏ��̃��[�v�ɍs��

		return true;
	}
	return false;
}
