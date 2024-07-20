#pragma once
#include <vector>
#include <functional>
#include "DxLib.h"
#include "..\Math\Vector.h"
#include "TextStatus.h"

//�e�L�X�g�`��N���X
class GameText {
private:
	//�����o�ϐ�
	static const int LOG_LINE_VALUE = 5;//�`��ł��镶����̍ő�l
	using add_text_function = std::function<void(std::vector<TextStatus>&)> ;//�^���������Ȃ�̂Ō^����錾
	add_text_function add_function = nullptr;//�������ǉ�����֐��̃|�C���^
	std::vector<TextStatus> texts;	//��������̃|�C���^
	Vector position = Vector(0, 0);	//�`�悷����W
	int font_size = 0;//�����̃T�C�Y

public:
	//�R���X�g���N�^
	GameText(Vector setPosition, std::vector<std::string> setTexts, int setColor, int fontSize, add_text_function set_function = nullptr);

	//�f�X�g���N�^
	~GameText();

	//�����o�֐�
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
};
