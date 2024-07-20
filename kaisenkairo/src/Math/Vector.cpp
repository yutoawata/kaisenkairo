#include"Vector.h"

//コンストラクタ
Vector::Vector(int setX, int setY) {
	x = (float)setX;
	y = (float)setY;
}
Vector::Vector(float setX, float setY) {
	x = setX;
	y = setY;
}

//ベクトル同士の加算を定義
Vector Vector::operator+(const Vector& other) {
	return Vector(x + other.x, y + other.y);
}

//ベクトルの減算の定義
Vector Vector::operator-(const Vector& other) {
	return Vector(x - other.x, y - other.y);
}

//ベクトルのスカラー値の乗算の定義
Vector Vector::operator*(float value) {
	return Vector(x * value, y + value);
}

//ベクトルとスカラー値の減算の定義
Vector Vector::operator/(float value) {
	
	if (value == 0)//00割対策
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

//自作ベクトルクラスをライブラリのベクトルクラスへのキャストを定義
Vector::operator VECTOR() {
	//2次元ベクトルなのでz軸の概念が存在しないので0で初期化
	return VGet(x, y, 0);
}

//単位ベクトル化して返す
Vector Vector::Normalize(Vector mine) {
	float mine_size = mine.getSize();//ベクトルの大きさを取得
	return Vector(mine.x / mine_size, mine.y / mine_size);
}