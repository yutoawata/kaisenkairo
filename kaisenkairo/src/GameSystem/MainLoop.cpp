#include "DxLib.h"
#include "GameMaster.h"
#include <crtdbg.h>

//���C���֐�
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//�Q�[���}�X�^�[�N���X���C���X�^���X
	GameMaster GM = GameMaster();
	
	GM.Run();//�Q�[�����[�v����
	
	return 0;
}