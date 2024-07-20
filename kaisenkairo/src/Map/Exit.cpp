#include "Exit.h"

//�R���X�g���N�^
UpExit::UpExit(Vector root, int exitMapId, int setColor)
	:ExitBase(exitMapId, setColor) {
	//���c��
	Vector start = root + Vector(0, THICKNESS);
	Vector end = root;
	Ray2 line = Ray2(start, end, color);
	lines.emplace_back(line);
	//����
	end = start + Vector(WIDTH, 0);
	line = Ray2(start, end, color);
	lines.emplace_back(line);
	//�E�c��
	start = end;
	end =start + Vector(0, -THICKNESS);
	line = Ray2(start, end, color);
	lines.emplace_back(line);

	position = end + Vector(-WIDTH / 2, 0);//���W��ۑ�
	//�R���C�_�[����ۑ�
	collider = new LineCollider(lines, position, ObjectType::UP_EXIT);
}

//�R���X�g���N�^
DownExit::DownExit(Vector root, int exitMapId, int setColor)
	:ExitBase(exitMapId, setColor) {
	//���c��
	Vector start = root + Vector(0, WIDTH - THICKNESS);
	Vector end = start + Vector(0, THICKNESS);
	Ray2 line = Ray2(start, end, color);
	lines.emplace_back(line);
	position = end + Vector(WIDTH / 2, 0);//���W��ۑ�
	//����
	end = start + Vector(WIDTH, 0);
	line = Ray2(start, end, color);
	lines.emplace_back(line);
	//�E�c��
	start = end;
	end = start + Vector(0, THICKNESS);
	line = Ray2(start, end, color);
	lines.emplace_back(line);

	//�R���C�_�[����ۑ�
	collider = new LineCollider(lines, position, ObjectType::DOWN_EXIT);
}

//�R���X�g���N�^
RightExit::RightExit(Vector root, int exitMapId, int setColor)
	:ExitBase(exitMapId, setColor) {
	//������
	Vector start = root + Vector(WIDTH - THICKNESS, 0);
	Vector end = start + Vector(THICKNESS, 0);
	Ray2 line = Ray2(start, end, color);
	lines.emplace_back(line);
	position = end + Vector(0, WIDTH / 2);
	//�c��
	end = start + Vector(0, WIDTH);
	line = Ray2(start, end, color);
	lines.emplace_back(line);
	//�㉡��
	start = end;
	end = start + Vector(THICKNESS, 0);
	line = Ray2(start, end, color);
	lines.emplace_back(line);

	//�R���C�_�[����ۑ�
	collider = new LineCollider(lines, position, ObjectType::RIGHT_EXIT);
}

//�R���X�g���N�^
LeftExit::LeftExit(Vector root, int exitMapId, int setColor)
	:ExitBase(exitMapId, setColor) {
	//�㉡��
	Vector start =root + Vector(THICKNESS, 0);
	Vector end = root;
	Ray2 line = Ray2(start, end, color);
	lines.emplace_back(line);
	//�c��
	end = start + Vector(0, WIDTH);
	line = Ray2(start, end, color);
	lines.emplace_back(line);
	//������
	start = end;
	end = start + Vector(-THICKNESS, 0);
	line = Ray2(start, end, color);
	lines.emplace_back(line);

	position = root + Vector(0, WIDTH / 2);//���W��ۑ�
	//�R���C�_�[����ۑ�
	collider = new LineCollider(lines, position, ObjectType::LEFT_EXIT);
}