#include "MapManager.h"

using namespace std;

//�R���X�g���N�^
MapManager::MapManager() {
	//�}�b�v����ۑ�
	SetUpMap();
}

//�f�X�g���N�^
MapManager::~MapManager() {
	for (int i = 0; i < stage_id.size(); i++) {
		delete maps[stage_id[i]];
		delete up_exits[stage_id[i]];
		delete down_exits[stage_id[i]];
		delete right_exits[stage_id[i]];
		delete left_exits[stage_id[i]];
	}
}

//���t�@�C���ł̌Ăяo��
MapManager& MapManager::Instance() {
	static MapManager Instance;
	return Instance;
}

void MapManager::Prepare() {
	maps[current_stage_id]->Prepare();
	up_exits[current_stage_id]->Prepare();
	down_exits[current_stage_id]->Prepare();
	right_exits[current_stage_id]->Prepare();
	left_exits[current_stage_id]->Prepare();
}

//�X�V����
void MapManager::Update() {
	//�J�b�g�C���t���O��ԂłȂ��Ȃ�
	if (!is_cutin) {
		maps[current_stage_id]->Update();

		ChangeMap();
	}
	//�J�b�g�C����ԂȂ�
	else {
		CutIn();
		is_change = false;
	}
		
}

//�`�揈��
void MapManager::Draw() {
	if (!is_cutin) {
		maps[current_stage_id]->Draw();

		up_exits[current_stage_id]->Draw();
		down_exits[current_stage_id]->Draw();
		right_exits[current_stage_id]->Draw();
		left_exits[current_stage_id]->Draw();
	}
	else {
		//�J���[�o�[��`��
		for (int i = 0; i < MAX_LINE_NUM; i++) {
			//�J���[�o�[�̒��i��`��
			DrawBox(position.getPosX() + (width * i), position.getPosY() + up_height,
				position.getPosX() + (width * (i + 1)), position.getPosY() + middle_height,
				color_02[i],
				TRUE);
			//�J���[�o�[�̉��i��`��
			DrawBox(position.getPosX() + (width * i), position.getPosY() + middle_height,
				position.getPosX() + (width * (i + 1)), position.getPosY() + down_height,
				color_03[i],
				TRUE);
			//���݂̃}�b�v�ɑΉ�����J���[�o�[�ł��� ���@�`�悵�Ȃ��^�C�~���O�Ȃ�
			if (i == static_cast<int>(current_stage_id) && (cutin_timer < 0.5f
				|| (cutin_timer > 1.0f && cutin_timer < 1.5f)))
				continue;

			//�J���[�o�[�̏�i��`��
			DrawBox(position.getPosX() + (width * i), position.getPosY(),
				position.getPosX() + (width * (i + 1)), position.getPosY() + up_height,
				color_01[i],
				TRUE);
		}
	}
}

//�o���̍��W��Ԃ�
Vector MapManager::getExitPosition(ObjectType type) {
	switch (type) {
	case ObjectType::UP_EXIT:
		//��̏o�����̍��W��Ԃ�
		return up_exits[current_stage_id]->getPosition();
		break;
	case ObjectType::DOWN_EXIT:
		//��̏o�����̍��W��Ԃ�
		return down_exits[current_stage_id]->getPosition();
		break;
	case ObjectType::RIGHT_EXIT:
		//��̏o�����̍��W��Ԃ�
		return right_exits[current_stage_id]->getPosition();
		break;
	case ObjectType::LEFT_EXIT:
		//��̏o�����̍��W��Ԃ�
		return left_exits[current_stage_id]->getPosition();
		break;
	default://�Ή����ĂȂ���ނȂ�
		return Vector(0, 0);//���_(���肦�Ȃ��l)��Ԃ�
		break;
	}
}

//�}�b�v�ԍ��z���int�^�z��Ƃ��ĕԂ�
vector<int> MapManager::getIntStageNum() {
	vector<int> map_num;//�Ԃ��z��
	for (int i = 0; i < stage_id.size();i++) {
		map_num.emplace_back(static_cast<int>(stage_id[i]));//int�^�ɃL���X�g���ĕۑ�
	}
	return map_num;
}

//�قȂ�}�b�v�Ɉړ������ۂ̃J�b�g�C������
void MapManager::CutIn() {
	//�J�b�g�C�����̌o�ߎ��Ԃ�����
	cutin_timer += FPSController::Instance().getDeltaTime();
	
	//�J�b�g�C���̕`�掞�Ԃ��߂�����
	if (cutin_timer > CUTIN_TIME) {
		is_cutin = false;
		cutin_timer = 0;//�o�ߎ��Ԃ̌v�������Z�b�g
	}
}

//�e�}�b�v���Ƃ̐�������ǂݍ���
void MapManager::SetUpMap() {
	//�}�b�v���̐���
	for (int i = 0; i < stage_id.size(); i++) {
		int stage_num = i;
		std::vector<Ray2> lines = LoadMapInfo(field_03, stage_id[i], stage_num++);
		maps[stage_id[i]] = new Map(lines, color_01[(int)stage_id[i]]);
	}

	UpdateLines();		//���݂̃}�b�v�����X�V
	UpdateCollider();	//�����蔻������X�V
}

//���݂̃}�b�v�̐������̍X�V
void MapManager::UpdateLines() {
	is_change = true;	//�}�b�v�J�ڃt���O��true�ɂ���
	is_cutin = true;	//�}�b�v�J�ڂȂ̂ŃJ�b�g�C���t���O��true�ɂ���
}

//�}�b�v�J�ڏ���
void MapManager::ChangeMap() {
	//������̏o�����Ƀv���C���[���Փ˂�����
	if (up_exits[current_stage_id]->CheckEnter()) {
		current_stage_id = (MapNum)up_exits[current_stage_id]->getNextStage();//���݂̃}�b�vID�̍X�V
		UpdateCollider();	//�o�����̃R���C�_�[���X�V
		UpdateLines();		//�}�b�v�̐�������ۑ�
	}
	//�������̏o�����Ƀv���C���[���Փ˂�����
	else if (down_exits[current_stage_id]->CheckEnter()) {
		current_stage_id = (MapNum)down_exits[current_stage_id]->getNextStage();//���݂̃}�b�vID�̍X�V
		UpdateCollider();	//�o�����̃R���C�_�[���X�V
		UpdateLines();		//�}�b�v�̐�������ۑ�
	}
	//�E�����̏o�����Ƀv���C���[���Փ˂�����
	else if (right_exits[current_stage_id]->CheckEnter()) {
		current_stage_id = (MapNum)right_exits[current_stage_id]->getNextStage();//���݂̃}�b�vID�̍X�V
		UpdateCollider();	//�o�����̃R���C�_�[���X�V
		UpdateLines();		//�}�b�v�̐�������ۑ�
	}
	//�������̏o�����Ƀv���C���[���Փ˂�����
	else if (left_exits[current_stage_id]->CheckEnter()) {
		current_stage_id = (MapNum)left_exits[current_stage_id]->getNextStage();//���݂̃}�b�vID�̍X�V
		UpdateCollider();//�o�����̃R���C�_�[���X�V
		//�}�b�v�̐�������ۑ�
		UpdateLines();
	}
}

//�e�R���C�_�[���̓o�^����
void MapManager::UpdateCollider() {
	ColliderManager::Instance().ClearColliders();
	//�X�V�����R���C�_�[��Collider�Ǘ��N���X�ɓn��
	ColliderManager::Instance().AddList(maps[current_stage_id]->getCollider());
	ColliderManager::Instance().AddList(up_exits[current_stage_id]->getCollider());
	ColliderManager::Instance().AddList(down_exits[current_stage_id]->getCollider());
	ColliderManager::Instance().AddList(right_exits[current_stage_id]->getCollider());
	ColliderManager::Instance().AddList(left_exits[current_stage_id]->getCollider());
}

//�o�����𐶐�
int MapManager::AddStageNum(int stageNum) {
	stageNum++;//�}�b�v�ԍ���i�߂�

	//�}�b�v�ԍ����}�b�v���𒴂�����
	if (stageNum == stage_id.size())
		stageNum = 0;//�}�b�v�ԍ������Z�b�g

	return stageNum;
}

//�����̐������𐶐�
Ray2 MapManager::GetStraightLine(Vector root, int lineColor, bool is_horizontal) {
	Vector start, end;
	float offset = GRID_LENGTH / 2;
	//�����𐶐�����Ȃ�Ȃ�
	if (is_horizontal == true) {
		start = Vector(root + Vector(0.0f, offset));	//���_
		end = Vector(start + Vector(GRID_LENGTH, 0));	//�I�_
	}
	//�c���𐶐�����Ȃ�
	else {
		start = Vector(root + Vector(offset, 0.0f));	//���_
		end = Vector(start + Vector(0, GRID_LENGTH));	//�I�_
	}
	return Ray2(start, end, lineColor);
}

//�p�̐������𐶐�
void MapManager::GetCornerLine(vector<Ray2>& lines, Vector root, int lineColor, bool is_up, bool is_right) {
	//��_�ƕǂ̒�����ۑ�
	float horizontal_offset = GRID_LENGTH / 2;
	float vartical_offset = GRID_LENGTH / 2;
	Vector start = Vector(root + Vector(horizontal_offset, horizontal_offset));

	//�p�̉������v�Z
	horizontal_offset = is_right ? -horizontal_offset : horizontal_offset;
	Vector end = Vector(start + Vector(horizontal_offset, 0.0f));
	//���𐶐�
	Ray2 horizontal_line(start, end, lineColor);
	//�z��ɕۑ�
	lines.emplace_back(horizontal_line);

	//�p�̏c���̌v�Z
	vartical_offset = is_up ? vartical_offset : -vartical_offset;
	end = Vector(start + Vector(0.0f, vartical_offset));
	Ray2 vertical_line(start, end, lineColor);
	lines.emplace_back(vertical_line);
}

//�}�b�v�`�b�v�ɑΉ������������𐶐�
void MapManager::CreateMap(vector<Ray2>& lines, Chip_Kind kind, int pos_x, int pos_y, MapNum mapNum, int& stageNum) {
	Ray2 line;//���������������
	int map_num = static_cast<int>(mapNum);
	int color = color_01[static_cast<int>(mapNum)];//�e���ā[���̕`�掞�̐F
	Vector MapPos = Vector(LEFT_LIMIT, UP_LIMIT);//�}�b�v�̊���W(����)
	//�O���b�h�P�ʂ̊���W(����)
	Vector root = Vector(MapPos + Vector(GRID_LENGTH * pos_x, GRID_LENGTH * pos_y));
	switch (kind) {
	case Chip_Kind::NONE_LINE://��������
		break;
	case Chip_Kind::VARTICAL://�c��
		line = GetStraightLine(root,  color, false);
		lines.emplace_back(line);
		break;
	case Chip_Kind::HORIZONTAL://����
		line = GetStraightLine(root,  color, true);
		lines.emplace_back(line);
		break;
	case Chip_Kind::LEFT_UP_CORNER://����(�l�p�`�)�̊p
		GetCornerLine(lines, root,  color, true, false);
		break;
	case Chip_Kind::RIGHT_UP_CORNER://�E��(�l�p�`�)�̊p
		GetCornerLine(lines, root,  color, true, true);
		break;
	case Chip_Kind::LEFT_DOWN_CORNER://����(�l�p�`�)�̊p
		GetCornerLine(lines, root,  color, false, false);
		break;
	case Chip_Kind::RIGHT_DOWN_CORNER://�E��(�l�p�`�)�̊p
		GetCornerLine(lines, root,  color, false, true);
		break;
	case Chip_Kind::UP_EXIT://������̏o����
		stageNum = AddStageNum(stageNum);
		//�e�X�e�[�W�̏o������ۑ�
		up_exits[stage_id[map_num]] = new UpExit(root, static_cast<int>(stage_id[stageNum]), color_01[stageNum]);
		//�}�b�v�̐������ɏo�����̏���ǉ�
		InsertLines(lines, up_exits[mapNum]->getLines());
		break;
	case Chip_Kind::DOWN_EXIT://������̏o����
		stageNum = AddStageNum(stageNum);
		//�e�X�e�[�W�̏o������ۑ�
		down_exits[stage_id[map_num]] = new DownExit(root, static_cast<int>(stage_id[stageNum]), color_01[stageNum]);
		//�}�b�v�̐������ɏo�����̏���ǉ�
		InsertLines(lines, down_exits[mapNum]->getLines());
		break;
	case Chip_Kind::RIGHT_EXIT://������̏o����
		stageNum = AddStageNum(stageNum);
		//�e�X�e�[�W�̏o������ۑ�
		right_exits[stage_id[map_num]] = new RightExit(root, static_cast<int>(stage_id[stageNum]), color_01[stageNum]);
		//�}�b�v�̐������ɏo�����̏���ǉ�
		InsertLines(lines, right_exits[mapNum]->getLines());
		break;
	case Chip_Kind::LEFT_EXIT://������̏o����
		stageNum = AddStageNum(stageNum);
		//�e�X�e�[�W�̏o������ۑ�
		left_exits[stage_id[map_num]] = new LeftExit(root, static_cast<int>(stage_id[stageNum]), color_01[stageNum]);
		//�}�b�v�̐������ɏo�����̏���ǉ�
		InsertLines(lines, left_exits[mapNum]->getLines());
		break;
	case Chip_Kind::ENEMY_POSITION://���̍��W
		//�Ή�����O���b�h���̒��S�����W�Ƃ��đ��
		enemy_positions[mapNum].emplace_back(root + Vector(GRID_LENGTH / 2, GRID_LENGTH / 2));
		break;
	default:
		break;
	}
}

vector<Ray2> MapManager::LoadMapInfo(int mapChips[FIELD_HIGHT][FIELD_WIDTH], MapNum mapNum, int stageNum) {
	std::vector<Ray2> lines;//���������}�b�v�̐������
	int wall_color = color_01[static_cast<int>(mapNum)];//�X�e�[�W�̕`�掞�̐F
	
	for (int y = 0; y < FIELD_HIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			//�}�b�v�`�b�v�ɉ����������̐���
  			CreateMap(lines, (Chip_Kind)mapChips[y][x], x, y, mapNum, stageNum);
		}
	}
	//�O�ǂ̐����𐶐��E�ۑ�
	Ray2 line;
	line = Ray2(Vector(LEFT_LIMIT, UP_LIMIT), Vector(RIGHT_LIMIT, UP_LIMIT), wall_color);
	lines.emplace_back(line);
	line = Ray2(Vector(RIGHT_LIMIT, UP_LIMIT), Vector(RIGHT_LIMIT, DOWN_LIMIT), wall_color);
	lines.emplace_back(line);
	line = Ray2(Vector(LEFT_LIMIT, DOWN_LIMIT), Vector(RIGHT_LIMIT, DOWN_LIMIT), wall_color);
	lines.emplace_back(line);
	line = Ray2(Vector(LEFT_LIMIT, UP_LIMIT), Vector(LEFT_LIMIT, DOWN_LIMIT), wall_color);
	lines.emplace_back(line);

  	return lines;//����������������Ԃ�
}