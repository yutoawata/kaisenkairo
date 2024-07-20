#pragma once
#include "DxLib.h"
#include "..\BaseClass\ObjectBase.h"
#include "..\ManagerClass\ColliderManager.h"
#include "..\Text\GameText.h"
#include "..\Color\Color.h"
#include "..\Math\Methods.h"
#include "View.h"

class Player : public ObjectBase {
private:
	//�����o�萔
	const int RADIUS = 20;			//�`�掞�̉~�̔��a
	const int MAX_HIT_POINT = 100;	//hit_point�̏��
	const int HALF_HIT_POINT = 50;	//hit_point�̔���
	const int MAX_LOG_LINE = 5;
	const float ROTATE_SPEED = 30.0f;	//���_�̉�]���x
	const float MOVE_SPEED = 1.5f;		//�ړ����x
	const float DAMAGE_INTERVAL = 0.2f;	//�_���[�W���󂯂銴�o
	const float ADD_LOG_INTERVAL = 2.0f;//���O��ǉ�����Ԋu

	//�����o�ϐ�
	std::vector<int> route;				//�ړ������}�b�v�̏�����ۑ�����z��
	std::vector<std::string> text;		//�e�L�X�g�\���N���X�ŕ\�����镶����
	CircleCollider* collider = nullptr;	//�����蔻��(�~)
	GameText* log = nullptr;	//�e�L�X�g�\���N���X
	View* view = nullptr;		//���E�`��N���X
	int hit_point = 100;		//�v���C���[��HP
	float angle = 0.0f;			//�����Ă���p�x
	float timer = 0.0f;			//�o�ߎ��Ԍv���ϐ�
	float move_timer = 0.0f;	//�ړ�����
	bool is_move = false;		//�ړ����Ă��邩�̃t���O
	bool can_add_log = false;	//���O��ǉ��ł��邩�̃t���O
	bool is_damage = false;		//�_���[�W���󂯂Ă��邩�̃t���O
	
public:
	//�R���X�g���N�^
	Player(Vector setPos, int setAngle, int fontSize);
	//�f�X�g���N�^
	~Player();

	//�A�N�Z�T
	inline CircleCollider GetCollider() { return *collider; }	//�����蔻��̏���n��
	inline Vector getPosition() { return position; }//�v���C���[�̍��W��n��
	inline int gethitPoint() { return hit_point; }	//HitPoint��Ԃ�
	inline bool getIsMove() { return is_move; }		//�ړ�������n��
	inline float getAngle() {return angle;}			//�����Ă���p�x

	//�����o�֐�
	//�X�V�O����
	void Prepare() override;
	//�X�V����
	void Update() override;
	//�`�揈��
	void Draw() override;
	//�S�[���ɒ��������̔��菈��
	bool CheckGoal(std::vector<int>stageId);
private:
	//�ړ�����
	void Move();
	//��]����
	void Rotate();
	//�_���[�W����
	void Damaged();
	//�����蔻�茋�ʂ̃`�F�b�N
	void CheckCollider();
	//�e�L�X�g�ǉ�����
	void AddLog(std::vector<TextStatus>& texts);
	//�}�b�v�ړ���̍��W�Ɉړ����鏈��
	void EnterRoom(ObjectType ExitType, Vector direction);
};