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
    if (!start_.init()) { return false; }

    return true;
}

//�X�V
int Game::update()
{
    if (!play)
    {
        if (!start_.update())
        {
            play = true;
        }
    }
    else
    {

        if (menu_type == 1)
        {
            menu_type = mino_.update();
        }
        else if (menu_type == 2) //�|�[�Y
        {
            //���j���[
            pausecnt = pause_.update();

        }
        else if (menu_type == 3) //�Q�[���I�[�o�[
        {

        }

        if (pausecnt == 2) //�Q�[���𑱂���
        {
            pausecnt = 0;
            menu_type = 1;
        }
        else if (pausecnt == 3) //���Z�b�g
        {
            pausecnt = 0;
            menu_type = 1;
            return 3;
        }
        else if (pausecnt == 4) //���C�����j���[
        {
            pausecnt = 0;
            menu_type = 1;
            return 4;
        }

        player_.update();
        ui_.update();
        pov_.update();
    }


    return 1;
}

//�`��
void Game::draw()
{
    ui_.draw(tetoris_s);
    ui_.inputdraw(tetoris_s);
    mino_.maindraw();
    mino_.nextdraw();
    mino_.holddraw();
    mino_.draw();

    if (!play)
    {
        start_.draw();
        start_.cntdraw();
        start_.godraw();
    }

    //�|�[�Y
    if (menu_type == 2)
    {
        pause_.draw();
        pause_.cursordraw();
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
    start_.destroy();
    pause_.destroy();
    player_.destroy();
    ui_.destroy();
    mino_.destroy();
}