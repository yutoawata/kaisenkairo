#pragma once
#include "..\BaseClass\ColliderBase.h"

//���̓����蔻��R���C�_�[�N���X
class LineCollider : public ColliderBase {
private:
	//�����o�ϐ�
	std::vector<Ray2> lines;	//�������(�n�_�E�I�_�E�F)
public:

	//�R���X�g���N�^
	LineCollider(std::vector<Ray2> setLines, Vector setPos, ObjectType setType);

	//�f�X�g���N�^
	~LineCollider();

	//�A�N�Z�T
	//��������Ԃ�
	inline const std::vector<Ray2>& getLines() { return lines; }

	//�����o�֐�
	//���W�̍X�V����
	void UpdateLines(std::vector<Ray2> newLines);
};