#include "Ray2.h"

//コンストラクタ
Ray2::Ray2() {}
//コンストラクタ
Ray2::Ray2(Vector setBegin, Vector setEnd, int setColor) {
	begin = setBegin;
	end = setEnd;
	color = setColor;
}
