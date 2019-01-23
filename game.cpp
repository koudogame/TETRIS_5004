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
    if (!mino_.init(0)) { return false; }
    if (!pause_.init()) { return false; }
    if (!start_.init()) { return false; }
    if (!clear_.init()) { return false; }

    play = false;

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
            menu_type = mino_.update(0);
            mino_.ghostupdate(0);
        }
        else if (menu_type == 2) //�|�[�Y
        {
            //���j���[
            pausecnt = pause_.update();

        }
        else if (menu_type == 3)
        {

        }
        else if (menu_type == 4) //�Q�[���I�[�o�[���g���C
        {

            return 3;
        }
        else if (menu_type == 5) //�Q�[���I�[�o�[���C�����j���[
        {
            return 4;
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
    ui_.draw(tetoris_s); //�w�i
    ui_.inputdraw(tetoris_s); //���͏��
    mino_.draw(0); //���������
    ui_.Hiddendraw(); //�B��
    mino_.maindraw(0); //�ςݏグ
    mino_.nextdraw(0); //�l�N�X�g
    mino_.holddraw(0); //�z�[���h
    mino_.leveldraw(0); //���x��
    mino_.scoredraw(0); //�X�R�A
    if (!play)
    {
        start_.draw(); //�X�^�[�g���j���[
        start_.cntdraw(); //�J�E���g�_�E��
        start_.godraw(); //GO!!
    }
    else
    {
        mino_.ghostdraw(0); //�S�[�X�g
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