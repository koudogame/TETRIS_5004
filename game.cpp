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
    if (!clear_.init()) { return false; }

    return true;
}

//�X�V
int Game::update(int player_num)
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
        else if (menu_type == 4) //�Q�[���N���A
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
    mino_.draw(0);
    ui_.Hiddendraw();
    mino_.maindraw(0);
    mino_.nextdraw(0);
    mino_.holddraw(0);
    mino_.leveldraw();

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

    //�Q�[���N���A
    if (menu_type == 4)
    {
        mino_.cleardraw();
    }
}

void Game::drawmulti()
{
    ui_.draw(tetris_multi);

    for (int i = 0; i < 4; i++)
    {
        mino_.draw(i);
        mino_.maindraw(i);
        mino_.nextdraw(i);
        mino_.holddraw(i);
    }

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

//�j��
void Game::destroy()
{
    start_.destroy();
    pause_.destroy();
    player_.destroy();
    ui_.destroy();
    mino_.destroy();
    clear_.destroy();
}