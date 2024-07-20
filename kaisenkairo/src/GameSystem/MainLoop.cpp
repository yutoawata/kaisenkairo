#include "DxLib.h"
#include "GameMaster.h"
#include <crtdbg.h>

//メイン関数
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//ゲームマスタークラスをインスタンス
	GameMaster GM = GameMaster();
	
	GM.Run();//ゲームループ処理
	
	return 0;
}