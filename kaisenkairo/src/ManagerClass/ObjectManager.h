#pragma once
#include "DxLib.h"
#include "..\Player\Player.h"
#include "..\Player\View.h"
#include "..\Enemy\Enemy.h"
#include "..\Text\GameText.h"
#include "MapManager.h"

class ObjectManager {
public:
	//�Q�[���i���󋵂̗񋓌^
	enum class ResultStatus {
		PLAY,		//�Q�[���i�s��
		CLEAR,		//�Q�[���N���A
		GAME_OVER	//�Q�[���I�[�o�[
	};

private:
	//�����o�ϐ�
	std::vector<Enemy*> enemys;	//�G��Object�̃N���X
	Player* player = nullptr;	//�v���C���[�N���X

	//�R���X�g���N�^
	ObjectManager();
	//�R�s�[�R���X�g���N�^���폜(Shingleton�p�^�[��)
	ObjectManager(const ObjectManager&) = delete;
public:
	//�f�X�g���N�^
	~ObjectManager();

	//���t�@�C���ł̌Ăяo���p�֐�
	static ObjectManager& Instance();
	//�A�N�Z�T
	//�v���C���N���X��Ԃ�
	inline Player getPlayer() { return *player; }		
	inline Vector getPlayerPosition() { return player->getPosition(); }

	//�����o�֐�
	//�X�V�O����
	void Prepare();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
	//�G�΃I�u�W�F�N�g�N���X�����֐�
	void EntryEnemy();
	//�v���C���[�N���X�����֐�
	void EntryPlayer(int logFontSize);
	//�Q�[���i���󋵂̔���֐�
	ResultStatus CheckResult(std::vector<int>stageId);
};