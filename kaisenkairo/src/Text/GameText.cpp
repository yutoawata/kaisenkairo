#include "GameText.h"

using namespace std;

//コンストラクタ
GameText::GameText(Vector setPosition, vector<string> setTexts, int setColor, int fontSize,
	add_text_function setFunction) {
	position = setPosition;
	font_size = fontSize;
	//TextStatusクラスとして保存
	for (string setText : setTexts) {
		texts.emplace_back(setText, setColor);
	}
	//テキスト追加処理があるなら
	if (setFunction != nullptr) {
		//関数ポインタを保存
		add_function = setFunction;
	}
}

//デストラクタ
GameText::~GameText() {
	texts.clear();
}

//更新処理
void GameText::Update() {
	//追加処理の関数ポインタがあるなら
	if (add_function != nullptr) {
		add_function(texts);//保存した関数を実行
	}
}

//描画処理
void GameText::Draw() {
	Vector sentence_pos;//描画するテキストの座標
	for (int i = 0; i < texts.size(); i++) {
		//要素が進む際に開業するために文字サイズ分下に下げる
		sentence_pos = position + Vector(0, font_size * i);
		DrawFormatString(sentence_pos.getPosX(), sentence_pos.getPosY(), texts[i].getColor(),
							"%s", (TCHAR*)texts[i].getCharText());
	}
}