#include "Exit.h"

//コンストラクタ
UpExit::UpExit(Vector root, int exitMapId, int setColor)
	:ExitBase(exitMapId, setColor) {
	//左縦線
	Vector start = root + Vector(0, THICKNESS);
	Vector end = root;
	Ray2 line = Ray2(start, end, color);
	lines.emplace_back(line);
	//横線
	end = start + Vector(WIDTH, 0);
	line = Ray2(start, end, color);
	lines.emplace_back(line);
	//右縦線
	start = end;
	end =start + Vector(0, -THICKNESS);
	line = Ray2(start, end, color);
	lines.emplace_back(line);

	position = end + Vector(-WIDTH / 2, 0);//座標を保存
	//コライダー情報を保存
	collider = new LineCollider(lines, position, ObjectType::UP_EXIT);
}

//コンストラクタ
DownExit::DownExit(Vector root, int exitMapId, int setColor)
	:ExitBase(exitMapId, setColor) {
	//左縦線
	Vector start = root + Vector(0, WIDTH - THICKNESS);
	Vector end = start + Vector(0, THICKNESS);
	Ray2 line = Ray2(start, end, color);
	lines.emplace_back(line);
	position = end + Vector(WIDTH / 2, 0);//座標を保存
	//横線
	end = start + Vector(WIDTH, 0);
	line = Ray2(start, end, color);
	lines.emplace_back(line);
	//右縦線
	start = end;
	end = start + Vector(0, THICKNESS);
	line = Ray2(start, end, color);
	lines.emplace_back(line);

	//コライダー情報を保存
	collider = new LineCollider(lines, position, ObjectType::DOWN_EXIT);
}

//コンストラクタ
RightExit::RightExit(Vector root, int exitMapId, int setColor)
	:ExitBase(exitMapId, setColor) {
	//下横線
	Vector start = root + Vector(WIDTH - THICKNESS, 0);
	Vector end = start + Vector(THICKNESS, 0);
	Ray2 line = Ray2(start, end, color);
	lines.emplace_back(line);
	position = end + Vector(0, WIDTH / 2);
	//縦線
	end = start + Vector(0, WIDTH);
	line = Ray2(start, end, color);
	lines.emplace_back(line);
	//上横線
	start = end;
	end = start + Vector(THICKNESS, 0);
	line = Ray2(start, end, color);
	lines.emplace_back(line);

	//コライダー情報を保存
	collider = new LineCollider(lines, position, ObjectType::RIGHT_EXIT);
}

//コンストラクタ
LeftExit::LeftExit(Vector root, int exitMapId, int setColor)
	:ExitBase(exitMapId, setColor) {
	//上横線
	Vector start =root + Vector(THICKNESS, 0);
	Vector end = root;
	Ray2 line = Ray2(start, end, color);
	lines.emplace_back(line);
	//縦線
	end = start + Vector(0, WIDTH);
	line = Ray2(start, end, color);
	lines.emplace_back(line);
	//下横線
	start = end;
	end = start + Vector(-THICKNESS, 0);
	line = Ray2(start, end, color);
	lines.emplace_back(line);

	position = root + Vector(0, WIDTH / 2);//座標を保存
	//コライダー情報を保存
	collider = new LineCollider(lines, position, ObjectType::LEFT_EXIT);
}