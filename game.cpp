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
    srand(time(NULL));
    //�����o������
    if (!ui_.init()) { return false;}
    if (!player_.init()) { return false; }
    if (!mino_.init()) { return false; }

    return true;
}

//�X�V
bool Game::update()
{
    minotype = rand() % 7;

    player_.update();
    ui_.update();
    pov_.update();
    mino_.update();

    return true;
}

//�`��
void Game::draw()
{
    ui_.draw();
    ui_.inputdraw(tetoris_s);
    mino_.draw();
    mino_.maindraw();
    
}

//�j��
void Game::destroy()
{
    start_.destroy();
    field_.destroy();
    player_.destroy();
    ui_.destroy();
    mino_.destroy();
    start_.destroy();
}