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
    if (!pause_.init()) { return false; }

    return true;
}

//�X�V
bool Game::update()
{
    if (menu_type == 1)
    {
        menu_type = mino_.update();
    }

    if (menu_type == 2)
    {
        //���j���[
        pause_.update();
    }
    player_.update();
    ui_.update();
    pov_.update();

    return true;
}

//�`��
void Game::draw()
{
    ui_.draw(tetoris_s);
    ui_.inputdraw(tetoris_s);
    mino_.draw();
    mino_.maindraw();
    mino_.nextdraw();
    mino_.holddraw();
    if (menu_type == 2)
    {
        //�|�[�Y
        pause_.draw();
    }
    else if(menu_type==3)
    {

        //�Q�[���I�[�o�[
        pause_.draw();

    }
    
}

void Game::drawmulti()
{
    ui_.draw(tetris_multi);
    mino_.draw();
    mino_.maindraw();
    mino_.nextdraw();
    mino_.holddraw();

}

//�j��
void Game::destroy()
{
    pause_.destroy();
    start_.destroy();
    field_.destroy();
    player_.destroy();
    ui_.destroy();
    mino_.destroy();
    start_.destroy();
}