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
bool Game::init()
{
    //�����o������

    return true;
}

//�X�V
bool Game::update()
{
    player_.update();
    ui_.update();

    return true;
}

//�`��
void Game::draw()
{
    ui_.draw();
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