#include"game.h"
#include<ctime>
#include<cstdlib>
//�R���X�g���N�^
Game::Game()
{
}

//�f�X�g���N�^
Game::~Game()
{
}

//������
bool Game::init(bool oba, int p2)
{


    //�����o������

    if (oba)
    {

    }


    return true;
}

//�X�V
bool Game::update(bool oba)
{
    field_.update(oba);
    player_.update(oba);
    ui_.update();
    if (!timelimit_.update())
    {
        return false;
    }
    return true;
}

//�`��
void Game::draw(bool oba)
{
    ui_.draw(); //�w�i
    field_.draw();
    field_.draw2();
    player_.draw(oba); //���搶
    player_.draw2();//���]��
    ui_.partitiondraw(); //�d�؂�
    ui_.meterdraw(); //�ߎ��������[�^�[
    timelimit_.draw(); //����
}

//�j��
void Game::destroy()
{
    start_.destroy();
    field_.destroy();
    player_.destroy();
    ui_.destroy();
    start_.destroy();
    timelimit_.destroy();
}