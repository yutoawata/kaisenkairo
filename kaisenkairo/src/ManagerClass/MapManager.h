#pragma once
#include <cmath>
#include <string>
#include "DxLib.h"
#include "..\Map\Exit.h"
#include "..\GameSystem\FPSController.h"
#include "..\Map\Map.h"
#include "..\Color\Color.h"
#include "ColliderManager.h"




class MapManager {
private:
	enum class MapNum {
		MAP_01,
		MAP_02,
		MAP_03,
		MAP_04,
		MAP_05,
		MAP_06,
		MAP_07
	};
	enum class Chip_Kind {
		NONE_LINE,			//�}�b�v�`�b�v����
		VARTICAL,			//�c��
		HORIZONTAL,			//����
		LEFT_UP_CORNER,		//����̊p
		RIGHT_UP_CORNER,	//�E��̊p
		LEFT_DOWN_CORNER,	//�����̊p
		RIGHT_DOWN_CORNER,	//�E���̊p
		UP_EXIT,			//�o��(��̕�)
		DOWN_EXIT,			//�o��(���̕�)
		RIGHT_EXIT,			//�o��(�E�̕�)
		LEFT_EXIT,			//�o��(���̕�)
		ENEMY_POSITION,		//�G�I�u�W�F�N�g�̈ʒu
	};
	//�����o�萔
	const std::vector<MapNum> stage_id//�}�b�v�̏���
		= { MapNum::MAP_01, MapNum::MAP_02, MapNum::MAP_03, MapNum::MAP_04, MapNum::MAP_05, MapNum::MAP_06, MapNum::MAP_07 };
	static const int MAX_LINE_NUM = 7;	//�J�b�g�C�����̃J���[�o�[�̖{��
	static const int CUTIN_TIME = 2;	//�J�b�g�C�������b���邩
	static const int FIELD_WIDTH = 17;	//�}�b�v�`�b�v�̗�
	static const int FIELD_HIGHT = 25;	//�}�b�v�`�b�v�̍s��
	static const int UP_LIMIT = 30;		//�}�b�v�`�b�v�̍��W��Y������
	static const int DOWN_LIMIT = 780;	//�}�b�v�`�b�v�̍��W��Y�����
	static const int RIGHT_LIMIT = 1910;//�}�b�v�`�b�v�̍��W��X�����
	static const int LEFT_LIMIT = 1400;	//�}�b�v�`�b�v�̍��W��X������
	static const int GRID_LENGTH = 30;	//�}�b�v�`�b�v�̑傫��

	//�����o�ϐ�
	//�}�b�v�`�b�v�B
	int field_03[FIELD_HIGHT][FIELD_WIDTH] = {
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 3, 2, 2, 2, 4, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,11, 0, 1, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0,},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0,},
	{0, 0, 0, 0,11, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0,},
	{2, 2, 2, 2, 2, 6, 0, 0, 0, 0, 0, 5, 2, 2, 2, 6, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 3, 2, 2, 4, 0, 0, 0, 0, 0, 0,},
	{10,0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,},
	{0, 0, 3, 2, 2, 4, 0, 1, 0, 0, 5, 2, 2, 2, 4, 0, 0,},
	{0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0,},
	{0, 0, 1, 0,11, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0,},
	{0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0,11, 0, 1, 0, 0,},
	{0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 3, 2, 2, 2, 6, 0, 0,},
	{0, 0, 5, 2, 2, 6, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 9,},
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 5, 2, 2, 6, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	};
	
	std::unordered_map<MapNum, Map*> maps;//�e�}�b�v�̃N���X
	std::unordered_map<MapNum, UpExit*> up_exits;		//�e�}�b�v�̏�œ�����N���X
	std::unordered_map<MapNum, DownExit*> down_exits;	//�e�}�b�v�̏�œ�����N���X
	std::unordered_map<MapNum, RightExit*> right_exits;	//�e�}�b�v�̏�œ�����N���X
	std::unordered_map<MapNum, LeftExit*> left_exits;	//�e�}�b�v�̏�œ�����N���X
	std::unordered_map<MapNum, std::vector<Vector>> enemy_positions;//�e�}�b�v�̓G�̈ʒu���W
	unsigned int color_01[MAX_LINE_NUM]//�J���[�o�[�̏�i�̐F(�}�b�v�̐F�����l)
		= { Color::WHITE, Color::YELLOW, Color::LIGHT_BLUE, Color::GREEN, Color::PURPLE, Color::RED, Color::BLUE };
	unsigned int color_02[MAX_LINE_NUM]//�J���[�o�[�̒��i�̐F
		= { Color::BLOCK, Color::BLUE,Color::PURPLE,Color::BLOCK, Color::LIGHT_BLUE, Color::BLOCK, Color::WHITE };
	unsigned int color_03[MAX_LINE_NUM]//�J���[�o�[�̉��i�̐F
		= { Color::DARK_BLUE, Color::BLOCK, Color::DARK_BLUE, Color::BLOCK, Color::BLOCK, Color::BLOCK, Color::BLOCK };

	Vector position = Vector(0, 0);	//Map�̍��W
	MapNum current_stage_id = MapNum::MAP_01;//���݂̃}�b�v��ID
	int width = 274;		//�J���[�o�[�̉���
	int up_height = 810;	//��i�J���[�o�[�̏c��
	int middle_height = 67 + up_height;		//���i�J���[�o�[�̏c��
	int down_height = 203 + middle_height;	//���i�J���[�o�[�̏c��
	float cutin_timer = 0;	//�J�b�g�C�����̌o�ߎ���
	bool is_close = true;	//�~�j�}�b�v�����Ă��邩�̃t���O
	bool is_sliding = false;//�~�j�}�b�v���J���ł��邩�̃t���O
	bool is_change = false;	//�}�b�v�J�ڃt���O
	bool is_cutin = false;	//�J�b�g�C���t���O

	//�R���X�g���N�^
	MapManager();
	MapManager(const MapManager&) = delete;

public:
	//�f�X�g���N�^
	~MapManager();

	//���t�@�C���ł̌Ăяo��
	static MapManager& Instance();

	//�A�N�Z�T
	//���݂̓G�N���X�̍��W��Ԃ�
	inline std::vector<Vector> getEnemyPosition() { return enemy_positions[current_stage_id]; }
	//���݂̃}�b�v�̐�������Ԃ�
	inline std::vector<Ray2> getMapLines() { return maps[current_stage_id]->getLines(); }
	//�}�b�vID�̔z���Ԃ�
	inline std::vector<MapNum> getStageId() { return stage_id; }
	//�}�b�vID��int�^�̔z��ŕԂ�
	std::vector<int> getIntStageNum();
	//�w�肵����ނ̏o�����̍��W��Ԃ���Ԃ�
	Vector getExitPosition(ObjectType type);
	//���݂̃}�b�v��ID��int�^�ŕԂ�
	inline int getCurrentStageId() { return static_cast<int>(current_stage_id); }
	//�}�b�v�J�ڃt���O��Ԃ�
	inline bool getIsChange() { return is_change; }
	//�J�b�g�C���t���O��Ԃ�
	inline bool getIsCutin() { return is_cutin; }
public:

	//�����o�֐�
	//�}�b�v���̏���
	void SetUpMap();
	//�X�V�O����
	void Prepare();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
private:
	//�}�b�v�J�ڏ���
	void ChangeMap();
	//�������̍X�V����
	void UpdateLines();	
	//�����蔻����̍X�V����
	void UpdateCollider();
	//�J�b�g�C������
	void CutIn();
	//�ԍ������Z
	int AddStageNum(int stageNum);
	//�p���쐬
	void GetCornerLine(std::vector<Ray2>& lines, Vector root, int lineColor, bool is_up, bool is_right);
	//�}�b�v�`�b�v���Ƃ̐����֐��Ăяo��
	void CreateMap(std::vector<Ray2>& lines, Chip_Kind kind, int pos_x, int pos_y, MapNum mapNum, int& stageNum);
	//MapChip������N���X�̔z��ɕϊ�����֐�
	std::vector<Ray2> LoadMapInfo(int mapChips[FIELD_HIGHT][FIELD_WIDTH], MapNum mapNum, int stageNum);
	//�c���E�������쐬
	Ray2 GetStraightLine(Vector root, int lineColor, bool is_horizontal);
};