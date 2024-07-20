#include "ObjectManager.h"

using namespace std;

//�R���X�g���N�^
ObjectManager::ObjectManager() {}

//�f�X�g���N�^
ObjectManager::~ObjectManager() {
	delete player;
	for (int i = 0; i < enemys.size(); i++) {
		delete enemys[i];
	}
}

//���t�@�C���ł̌Ăяo���p�֐�
ObjectManager& ObjectManager::Instance() {
	static ObjectManager instance;
	return instance;
}

//�v���C���[�֘A�̃N���X��������
void ObjectManager::EntryPlayer(int logFontSize) {
	delete player;
	player = new Player(Vector(1600, 750),0,logFontSize);//�v���C���[�I�u�W�F�N�g��������
}

//�G�N���X��������
void ObjectManager::EntryEnemy() {
	//�}�b�v�Ǘ��N���X����J�ڌ�̃}�b�v�̃G�l�~�[�̍��W�z����擾
	vector<Vector> positions = MapManager::Instance().getEnemyPosition();
	int enemys_size = static_cast<int>(enemys.size());
	for (int i = 0; i < enemys_size; i++)
		delete enemys[i];//�J�ڑO�̃G�l�~�[���폜

	enemys.clear();//�폜�����G�l�~�[�̃|�C���^���폜
	for (Vector position : positions) 
		enemys.emplace_back(new Enemy(position));
}

//�Q�[���̃v���C����
ObjectManager::ResultStatus ObjectManager::CheckResult(vector<int> stageId) {
	//�v���C���[���i�񂾃}�b�v�̏��Ԃ��������Ȃ�
	if (player->CheckGoal(stageId)) 
		return ResultStatus::CLEAR;//�N���A

	//�v���C���[���i�񂾃}�b�v�̏��Ԃ��Ԉ���Ă���@�܂��́@�v���C���[��HP��0�ɂȂ����Ȃ�
	if (player->gethitPoint() == 0) 
		return ResultStatus::GAME_OVER;//�Q�[���I�[�o�[
	
	//�����𖞂����ĂȂ��̂�
	return ResultStatus::PLAY;//�Q�[���𑱍s
}

//�X�V�O����
void ObjectManager::Prepare() {
	player->Prepare();//�v���C���[�N���X�̍X�V�O����

	for (int i = 0; i < enemys.size(); i++)
		enemys[i]->Prepare();//�e�G�N���X�̍X�V�O����
	
}

//�X�V����
void ObjectManager::Update() {
	//�}�b�v���J�ڂ����Ȃ�
	if (MapManager::Instance().getIsChange()) 
		//�J�ڌ�̃}�b�v�}�b�v���ɂ������G�l�~�[�𐶐�
		EntryEnemy();
	
	player->Update();//�v���C���[�N���X�̍X�V����

	for (int i = 0; i < enemys.size(); i++) 
		enemys[i]->Update();//�e�G�N���X�̍X�V����
	
}

//�`�揈��
void ObjectManager::Draw() {
	player->Draw();//�v���C���[�̕`�揈��
}