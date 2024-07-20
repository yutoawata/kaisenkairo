#include"Vector.h"

//�R���X�g���N�^
Vector::Vector(int setX, int setY) {
	x = (float)setX;
	y = (float)setY;
}
Vector::Vector(float setX, float setY) {
	x = setX;
	y = setY;
}

//�x�N�g�����m�̉��Z���`
Vector Vector::operator+(const Vector& other) {
	return Vector(x + other.x, y + other.y);
}

//�x�N�g���̌��Z�̒�`
Vector Vector::operator-(const Vector& other) {
	return Vector(x - other.x, y - other.y);
}

//�x�N�g���̃X�J���[�l�̏�Z�̒�`
Vector Vector::operator*(float value) {
	return Vector(x * value, y + value);
}

//�x�N�g���ƃX�J���[�l�̌��Z�̒�`
Vector Vector::operator/(float value) {
	
	if (value == 0)//00���΍�
		return Vector(0, 0);

	return Vector(x / value, y / value);
}

Vector& Vector::operator +=(const Vector& other) {
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Vector& Vector::operator -=(const Vector& other) {
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

bool Vector::operator==(const Vector& other) {
	return (x == other.x && y == other.y);
}

//����x�N�g���N���X�����C�u�����̃x�N�g���N���X�ւ̃L���X�g���`
Vector::operator VECTOR() {
	//2�����x�N�g���Ȃ̂�z���̊T�O�����݂��Ȃ��̂�0�ŏ�����
	return VGet(x, y, 0);
}

//�P�ʃx�N�g�������ĕԂ�
Vector Vector::Normalize(Vector mine) {
	float mine_size = mine.getSize();//�x�N�g���̑傫�����擾
	return Vector(mine.x / mine_size, mine.y / mine_size);
}