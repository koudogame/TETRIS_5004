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
        //��ꃂ�[�h
        if (!player_.init(L"oba1.png", L"�`����.png"))return false;
    }
    else
    {
        if (p2 == 0)
        {
            if (!player_.init(L"car_side.png", L"�`����.png"))return false;
        }
        if (p2 == 1)
        {
            if (!player_.init(L"car_side.png", L"�o�C�N��.png"))return false;
        }
        if (p2 == 2)
        {
            if (!player_.init(L"car_side.png", L"�o�C�N��.png"))return false;
        }
    }

    if (!ui_.init()) return false;
    if (!timelimit_.init(L"work8.png")) return false;
    if (!field_.init())return false;
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