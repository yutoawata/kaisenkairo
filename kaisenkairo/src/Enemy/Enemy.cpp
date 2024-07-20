#include "Enemy.h"

//�R���X�g���N�^
Enemy::Enemy(Vector setPos)
	: ObjectBase(setPos) {
	position = setPos;
	home_pos = setPos;
	collider = new CircleCollider(position, 90, ObjectType::ENEMY);
	ColliderManager::Instance().AddList(collider);
}

//�f�X�g���N�^
Enemy::~Enemy() {
	delete collider;
}

//�X�V�O����
void Enemy::Prepare() {
	//�R���C�_�[�������Z�b�g
	collider->Reset();
}

//�X�V����
void Enemy::Update() {
	//�ړ�����ړI�n(�������l:�X�|�[�����W)
	Vector target_position = home_pos;

	for (ColliderBase other : collider->getOthers()) {
		//������������̎�ނ��擾
		ObjectType ohter_type = other.getType();

		//Player�Ɠ������Ă���Ȃ�
		if (ohter_type == ObjectType::PLAYER) {
			//������������̍��W��ړI�n�ɂ���
			target_position = other.getPosition();
			break;
		}
	}
	Move(target_position);//�ړ�����
}

//�`�揈��
void Enemy::Draw() {
	//���g�̍��W���~�ŕ`��
	DrawCircle(position.getPosX(), position.getPosY(), radius, Color::RED, TRUE);
}

//�ړ�����
void Enemy::Move(Vector targetPos) {
	Vector direction = targetPos - position;	//�ړ�����
	float direction_size = direction.getSize();	//�ړ���Ƃ̋���

	//���������̈ړ�����艓�����
	if (direction_size >= speed) {
		Vector normal_direction = Vector::Normalize(direction);
		//�ړ���̍��W����
		position = position + Vector(normal_direction.getX() * speed, normal_direction.getY() * speed);
		//�R���C�_�[�̍��W���X�V
		collider->UpdatePosition(position);
	}
}