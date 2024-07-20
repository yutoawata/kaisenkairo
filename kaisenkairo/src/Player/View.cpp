#include "View.h"

using namespace std;

//�R���X�g���N�^
View::View() {
	//�m�C�Y�̕`����W�𗐐��Ő���
	for (int i = 0; i < MAX_NOISE_NUM; i++) {
		noise_pos[i] = Vector(CreateRandom(min_x, max_x), CreateRandom(min_y, max_y));
	}
}

Vector View::CheckMinDistanceWall(Ray2 viewRay, Vector playerPos, int& color) {
	vector<Ray2> map_lines = MapManager::Instance().getMapLines();//map�̐������̃R�s�[
	Vector min_dist_cross = Vector(NULL, NULL);//�ŒZ�����̌�_�̍��W
	float min_dist = 0;		//�ŒZ����
	bool is_first = true;	//��ڂ̌�_���̃t���O

	//map�̐�������for���ň�{���m�F���čs��
	for (int i = 0; i < map_lines.size(); i++) {
		Vector cross_pos = Intersection(map_lines[i], viewRay);//���E����̐���map�̐����Ƃ̌�_
		Vector distance_vec = cross_pos - playerPos;
		float distance = distance_vec.getSize();
		//��_���������Ă����Ȃ�
		if (!cross_pos.IsZero()) {
			//��ڂ̌�_�Ȃ�
			if (is_first) {
				min_dist_cross = cross_pos;		//��Ƃ��邽�߂ɍŒZ�����̌�_�̒l�ɑ������
				color = map_lines[i].getColor();//��ԋ߂���_���X�V���ꂽ��`�悷������̐F���X�V
				min_dist = distance;//��Ƃ��邽�߂ɋ����̍ŏ��l�̒l�ɑ������
				is_first = false;	//�ȍ~�̌�_�͈�ڂł͂Ȃ��̂Ńt���O��؂�
			}
			//��ڈȍ~�̌�_ ���@�ۑ����ꂽ�ŒZ�������Z���Ȃ�
			else if (!is_first && distance < min_dist) {
				min_dist_cross = cross_pos;			//�ŒZ�����̌�_�̍��W���X�V
				min_dist = distance;				//�ŒZ�����̒l���X�V
				color = map_lines[i].getColor();	//��ԋ߂���_���X�V���ꂽ��`�悷������̐F���X�V
			}
		}
	}
	return min_dist_cross;
}

void View::Draw(Vector playerPos, float playerAngle) {
	float left_angle = playerAngle - (float)M_PI_4;	//��`�̍��[�̊p�x
	float right_angle = playerAngle + (float)M_PI_4;//��`�̉E�[�̊p�x
	int line_num = 0;//�������̐������{�ڂȂ̂���ۑ�

	//��`�̎���͈͂�W�J
	for (float angle = left_angle; angle < right_angle; angle += (float)M_PI_2 / RAY_NUM) {
		//����̐����̏I�_���Z�o
		Vector end_pos = Vector(playerPos + Vector(cos(angle) * range, sin(angle) * range));
		Ray2 view_ray(playerPos, end_pos);	//���씻��̐���
		int color = Color::WHITE;			//�`�掞�̐F
		//�ł��߂���_���Z�o
		Vector min_dist_cross = CheckMinDistanceWall(view_ray, playerPos, color);

		//��_���Ȃ��Ȃ�
		if (min_dist_cross.IsZero()) 
			min_dist_cross = end_pos;//�I�_�͂��̂܂�
		else {
			//Player�̎���̐����̕`�揈��
			DrawViewRenge(playerPos, min_dist_cross);

			Vector distance_vec = min_dist_cross - playerPos;
			float distance = distance_vec.getSize() * cos(angle - playerAngle);//��L�̃x�N�g���̒���
			float view_height = Clump(14000.0f / distance, 0.0f, (float)HEIGHT_LIMIT);	//�`�悷����̒���
			//��l�̎��_�̕`�揈��
			DrawFPSView(line_num, color, view_height);
		}
		line_num++;
	}
}

void View::DrawViewRenge(Vector playerPos, Vector crossPos) {
	Ray2 sight(playerPos, crossPos);//����̐���(�n�_,�I�_)
	//�������ŕ`��
	DrawLine(sight.getBegin().getPosX(), sight.getBegin().getPosY(),//���_
				sight.getEnd().getPosX(), sight.getEnd().getPosY(),	//�I�_
				Color::WHITE);//�����̐F
}

//1�l�̎��_��`��
void View::DrawFPSView(int lineNum, int color, float viewHeight) {
	Vector view_root = Vector(50, 380);//�`������̍��W�̊
	Vector line_begin = view_root + Vector((float)(4 * lineNum), -viewHeight / 2.0f);//�n�_
	Vector line_end = line_begin + Vector(0.0f, viewHeight);//�I�_
	
	//�����̕`��֐�
	DrawLine(line_begin.getPosX(), line_begin.getPosY(), line_end.getPosX(), line_end.getPosY(), color);
}

void View::DrawNoise(bool isAddNoise) {
	//�o�ߎ��Ԃ̌v��
	timer += FPSController::Instance().getDeltaTime();
	//�m�C�Y�̌���0�`60�ɐ���
	noise_num = Clump(noise_num, MIN_NOISE_NUM, MAX_NOISE_NUM);
	
	if (timer >= ADD_NOISE_INTERVAL) {
		if (isAddNoise)	
			noise_num++;
		else
			noise_num--;

		timer = 0;//�o�ߎ��Ԃ����Z�b�g
	}

	//���������������m�C�Y��`�悷��
	for (int i = 0; i < noise_num; i++) {
		int pos_x = noise_pos[i].getPosX();//�`�悷����W��X��������
		int pos_y = noise_pos[i].getPosY();//�`�悷����W��Y��������
		//�w��̍��W�������l�p�`��`��
		DrawBox(pos_x, pos_y, pos_x + width, pos_y + height, Color::BLOCK, TRUE);
		//��L�̎l�p�`�𔒐��ň͂�
		DrawLine(pos_x,			pos_y,			pos_x + width, pos_y,		   Color::WHITE);//�㉡��
		DrawLine(pos_x,			pos_y + height, pos_x,		   pos_y,		   Color::WHITE);//���c��
		DrawLine(pos_x + width, pos_y,			pos_x + width, pos_y + height, Color::WHITE);//�E�c��
		DrawLine(pos_x + width, pos_y + height, pos_x,		   pos_y + height, Color::WHITE);//������
	}
}
