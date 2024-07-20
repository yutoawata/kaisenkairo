#include "Player.h"

using namespace std;

//�R���X�g���N�^
Player::Player(Vector setPos, int setAngle, int fontSize)
	:ObjectBase(setPos, Color::YELLOW) {
	collider = new CircleCollider(position, RADIUS, ObjectType::PLAYER);
	ColliderManager::Instance().AddList(collider);
	route.emplace_back(0);
	view = new View();
	/*
		AddLog���Ăяo�������_����n�����ƂŁA
		�����o�֐����N���X���w�肵�Ă��Ȃ��֐��|�C���^�Ƃ��ēn��
	*/
	std::function<void(std::vector<TextStatus>&)> set_func =
		[this](std::vector<TextStatus>& texts) {AddLog(texts); };
	std::vector<std::string> texts = { " "," "," "," "," " };
	log = new GameText(Vector(50, 840), texts, Color::WHITE, fontSize, set_func);
}

//�f�X�g���N�^
Player::~Player() {
	delete log;
	delete view;
	delete collider;
}

//�X�V�O����
void Player::Prepare() {
	is_move = false;
	is_damage = false;
	collider->Reset();
	Move();
	Rotate();
	/*
		�����ňړ��������s���̂́A�Փˏ�������������ɂ�����A
		�ړ������ƁA���W�̍X�V�̊Ԃɓ����蔻�菈�����s���������߁B
	*/
}

//�X�V����
void Player::Update() {
	CheckCollider();

	if (is_move) {
		//�ړ����Ԃ��v��
		move_timer += FPSController::Instance().getDeltaTime();
		position = collider->getPosition();//���W���X�V
	}
	else
		collider->UpdatePosition(position);//�ړ��ł��Ȃ��̂Ō��̍��W�ɖ߂�

	Damaged();		//�_���[�W����
	log->Update();	//���O�̍X�V����
}

//�`�揈��
void Player::Draw() {
	view->Draw(position, angle);//��l�̎��_��`��
	view->DrawNoise(is_damage);	//�_���[�W��Ԃ̕`��
	log->Draw();//�s�����O�̕`��

	//���g�̍��W���~�ŕ\��
	DrawCircle(position.getPosX(), position.getPosY(), RADIUS, color, TRUE);
}


//�\������e�L�X�g��ǉ�
void Player::AddLog(vector<TextStatus>& texts) {
	//2�b�Ԉړ������Ȃ�
	if (move_timer >= ADD_LOG_INTERVAL) {
		texts.insert(texts.begin(), TextStatus("�U�U�@.....", Color::WHITE));
		move_timer = 0.0f;//�ړ����Ԃ����Z�b�g
	}
	//hit_point��100�E50�̂����ꂩ�ɂȂ����Ȃ�
	if (hit_point % HALF_HIT_POINT == 0&& can_add_log) {
		//�\������e�L�X�g���쐬
		string new_text = "���݂�HP:" + to_string(hit_point);
		
		if (hit_point == MAX_HIT_POINT)
			texts.insert(texts.begin(), TextStatus(new_text, Color::GREEN));//��L�̓��e��z��̍Ō���ɒǉ�
		else if(hit_point==HALF_HIT_POINT)
			texts.insert(texts.begin(), TextStatus(new_text, Color::RED));//��L�̓��e��z��̍Ō���ɒǉ�
		
		
		can_add_log = false;
	}

	if (texts.size() > MAX_LOG_LINE)
		texts.erase(texts.end() - 1);
}

//�ړ�����
void Player::Move() {
	Vector move_pos = position;//�ړ���̍��W
	
	if (CheckHitKey(KEY_INPUT_A)) {
		is_move = true;
		//�������̕����x�N�g�����Z�o
		Vector left = CreateVector(angle - static_cast<float>(M_PI_2), MOVE_SPEED);
		move_pos = move_pos - left;//�������Ɉړ�
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		is_move = true;
		//�ړ��������v�Z
		Vector right = CreateVector(angle + static_cast<float>(M_PI_2), MOVE_SPEED);
		move_pos = move_pos - right;//�E�����Ɉړ�
	}
	if (CheckHitKey(KEY_INPUT_W)) {
		is_move = true;
		//�ړ������x�N�g�����Z�o
		Vector forward = CreateVector(angle, MOVE_SPEED);
		move_pos = move_pos - forward;//�O�����Ɉړ�
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		is_move = true;
		//�ړ��������v�Z
		Vector back = CreateVector(angle - static_cast<float>(M_PI), MOVE_SPEED);
		move_pos = move_pos - back;//�������Ɉړ�
	}

	//�R���C�_�[�Ɉړ���̍��W����
	collider->UpdatePosition(move_pos);
}

//��]����
void Player::Rotate() {
	//�}�E�X�J�[�\���̍��W����
	int cursor_x, cursor_y;
	//�}�E�X�J�[�\���̈ʒu���擾
	GetMousePoint(&cursor_x, &cursor_y);

	//���S���E���͂Ȃ�
	if (960 < cursor_x)
		//�E��U�����
		angle += static_cast<float>(M_PI_4) / ROTATE_SPEED;
	//���S��荶���͂Ȃ�
	else if (960 > cursor_x) 
		//����U�����
		angle -= static_cast<float>(M_PI_4) / ROTATE_SPEED;

	//�p�x�����������
	if (angle > static_cast<float>(M_PI) * 2)
		//��T���̊p�x������
		angle -= static_cast<float>(M_PI) * 2;
}

//���������ꍇ�̏���
void Player::CheckCollider() {
	//������������̎�ނ�����
	for (ColliderBase other : collider->getOthers()) {
		ObjectType other_type = other.getType();
		//�ǂɓ������Ă����
		if (other_type == ObjectType::WALL)
			//�ړ��t���O��false��
			is_move = false;
		
		else if (other_type == ObjectType::UP_EXIT || other_type == ObjectType::DOWN_EXIT ||
			other_type == ObjectType::RIGHT_EXIT || other_type == ObjectType::LEFT_EXIT) {
			is_move = false;//�ړ��t���O��false��;
			//������������̍��W���擾
			Vector direction = other.getPosition() - position;
			//�}�b�v�Ԉړ��������s��
			EnterRoom(other_type, direction);
		}
		else if (other_type == ObjectType::ENEMY)
			is_damage = true;
	}
}

void Player::Damaged() {

	if (is_damage) {
		//�o�ߎ��Ԃ��v��
		timer += FPSController::Instance().getDeltaTime();
		//0.5�b����HitPoint��1���炷
		if (timer >= DAMAGE_INTERVAL) {
			can_add_log = true;
			hit_point--;//HP�����炷
			timer = 0;	//�o�ߎ��Ԃ����Z�b�g
		}
	}
	//�_���[�W���󂯂Ă��Ȃ��Ȃ�
	else {
		//HP�̏���ɒB���Ă��Ȃ��Ȃ�
		if (hit_point != MAX_HIT_POINT) {
			//�o�ߎ��Ԃ��v��
			timer += FPSController::Instance().getDeltaTime();
			////0.5�b����HitPoint��1���炷
			if (timer >= DAMAGE_INTERVAL) {
				can_add_log = true;
				hit_point++;//HP�𑝂₷
				timer = 0;	//�o�ߎ��Ԃ����Z�b�g
			}
		}
	}
}

//�}�b�v�Ԃ̈ړ����̏���
void Player::EnterRoom(ObjectType exitType, Vector direction) {
	Vector enter_position = Vector(0, 0);//�ړ���̓�����̍��W
	enter_position = MapManager::Instance().getExitPosition(ExitBase::GetEnterType(exitType));

	float melt_value = 2.0f;
	//���̃X�e�[�W�Ɉړ���������ƐڐG������ԂŃX�^�[�g���Ȃ��悤�Ɉړ��ʂ̃x�N�g����{�ɂ��邷��
	Vector enter_direction = Vector(direction.getX() * melt_value, direction.getY() * melt_value);
	position = direction + enter_position;	//�ړ���̍��W����
	collider->UpdatePosition(position);		//�R���C�_�[�̍��W���X�V
	int num = MapManager::Instance().getCurrentStageId();//�ړ���̃}�b�v�ԍ����擾
	route.emplace_back(num);//�}�b�v�ԍ����ړ��������[�g�ɕۑ�
}


//�S�[���������̃`�F�b�N
bool Player::CheckGoal(vector<int> stageId) {
	int num = 0;//�������Ă���}�b�v�̏���
	//�ʂ���map�̏��Ԃ�����
	for (int map : route) {
		//�ʂ����}�b�v�̏��Ԃ��Ⴄ�Ȃ�
		if (map != stageId[num]) {
			route.clear();//���������Z�b�g
			return false;
		}
		num++;
	}

	//�ʂ����}�b�v�̏��Ԃ��r���Ȃ�
	if (route.size() != stageId.size())
		return false;

	//������̏����ɂ��Y�����Ȃ��Ȃ�
	return true;
}