#include "DxLib.h"
#include "..\Collider\LineCollider.h"

//�o����
class ExitBase {
protected:
	//�����o�萔
	static const int THICKNESS = 10;//����
	static const int WIDTH = 30;	//��

	//�����o�ϐ�
	std::vector<Ray2> lines;			//����
	LineCollider* collider = nullptr;	//�����蔻��
	Vector position = Vector(0, 0);		//���W
	int color = Color::WHITE;			//���݂̐F
	int next_map_id = 0;//�q����}�b�v��ID
	

public:
	//�R���X�g���N�^
	ExitBase(int exitMapId, int setColor);

	//�f�X�g���N�^
	virtual ~ExitBase();

	//�A�N�Z�T
	//�����蔻�����Ԃ�
	inline LineCollider* getCollider() { return collider; }
	//�����z���Ԃ�
	inline const std::vector<Ray2>& getLines() { return lines; }
	//���W��Ԃ�
	inline Vector getPosition() { return position; }
	//�J�ڐ�̃}�b�v��ID��Ԃ�
	inline int getNextStage() { return next_map_id; }

	//�����o�֐�
	//�X�V����
	void Prepare();
	//�`�揈��
	void Draw();
	//���ꔻ�菈��
	bool CheckEnter();
	
	//�w�肵���o�����ɑΉ�����o������Ԃ�
	static ObjectType GetEnterType(ObjectType exitType);
};
