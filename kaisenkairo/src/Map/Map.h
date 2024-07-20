#pragma once
#include <vector>
#include "DxLib.h"
#include "..\Color\Color.h"
#include "..\Math\Methods.h"
#include "..\BaseClass\ObjectBase.h"
#include "..\Collider\LineCollider.h"
#include "Exit.h"

class Map : public ObjectBase {
private:
	//�����o�ϐ�
	LineCollider* collider;	//�ǂ̓����蔻��
	std::vector<Ray2> lines;//map�̐������̔z��
	bool is_search = false;	//�T�[�`�@�\���g�p���Ă��邩�̃t���O
	int timer = 0;			//�T�[�`���̌o�ߎ��Ԃ��v��
	int radius = 0;			//�T�[�`�͈͂̔��a

public:
	//�R���X�g���N�^
	Map(std::vector<Ray2> setLines, int setColor, Vector setPos = Vector(1400, 30));
	~Map();

	//�A�N�Z�T
	inline LineCollider* getCollider() { return collider; }	//map�̓����蔻�����Ԃ�
	inline const std::vector<Ray2>& getLines() { return lines; }//��������Ԃ�
	inline int getSize() { return static_cast<int>(lines.size()); }			//�����z��̗v�f����Ԃ�

	//�����o�֐�
	//�X�V�O����
	void Prepare() override;
	//�X�V����
	void Update() override;
	//�`�揈��
	void Draw() override;
	//�}�b�v�M�~�b�N
	void Search();
};