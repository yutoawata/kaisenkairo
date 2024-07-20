#include "Map.h"

//�R���X�g���N�^
Map::Map(std::vector<Ray2> setLines, int setColor, Vector setPos)
	: ObjectBase(setPos) {
	position = setPos;
	lines = setLines;
	color = setColor;
	collider = new LineCollider(setLines, position, ObjectType::WALL);
}

//�f�X�g���N�^
Map::~Map() {}

//�X�V�O����
void Map::Prepare() {
	collider->Reset();//�����蔻����̃��Z�b�g
}

//�X�V����
void Map::Update() {
	Search();//���G����
}

//�`�揈��
void Map::Draw() {
	//�}�b�v��`��
	for (int i = 0; i < lines.size(); i++) {
		DrawLine(lines[i].getBegin().getPosX(), lines[i].getBegin().getPosY(),	//�n�_ 
				 lines[i].getEnd().getPosX(),	lines[i].getEnd().getPosY(),	//�I�_
				 Color::WHITE//�`�掞�̐F
		);
	}
}

void Map::Search() {
	if (CheckHitKey(KEY_INPUT_R))
		is_search = true;

	if (is_search) {
		if (timer >= 300) {
			is_search = false;
			timer = 0;
		}
	}
}