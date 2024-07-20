#include "GameText.h"

using namespace std;

//�R���X�g���N�^
GameText::GameText(Vector setPosition, vector<string> setTexts, int setColor, int fontSize,
	add_text_function setFunction) {
	position = setPosition;
	font_size = fontSize;
	//TextStatus�N���X�Ƃ��ĕۑ�
	for (string setText : setTexts) {
		texts.emplace_back(setText, setColor);
	}
	//�e�L�X�g�ǉ�����������Ȃ�
	if (setFunction != nullptr) {
		//�֐��|�C���^��ۑ�
		add_function = setFunction;
	}
}

//�f�X�g���N�^
GameText::~GameText() {
	texts.clear();
}

//�X�V����
void GameText::Update() {
	//�ǉ������̊֐��|�C���^������Ȃ�
	if (add_function != nullptr) {
		add_function(texts);//�ۑ������֐������s
	}
}

//�`�揈��
void GameText::Draw() {
	Vector sentence_pos;//�`�悷��e�L�X�g�̍��W
	for (int i = 0; i < texts.size(); i++) {
		//�v�f���i�ލۂɊJ�Ƃ��邽�߂ɕ����T�C�Y�����ɉ�����
		sentence_pos = position + Vector(0, font_size * i);
		DrawFormatString(sentence_pos.getPosX(), sentence_pos.getPosY(), texts[i].getColor(),
							"%s", (TCHAR*)texts[i].getCharText());
	}
}