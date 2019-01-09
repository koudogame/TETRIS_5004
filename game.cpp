#include"game.h"
#include<ctime>
#include<cstdlib>
//コンストラクタ
Game::Game()
{
}

//デストラクタ
Game::~Game()
{
}

//初期化
bool Game::init()
{
    srand(time(NULL));
    //メンバ初期化
    if (!ui_.init()) { return false;}
    if (!player_.init()) { return false; }
    if (!mino_.init()) { return false; }
    if (!pause_.init()) { return false; }
    if (!start_.init()) { return false; }
    if (!clear_.init()) { return false; }

    return true;
}

//更新
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
        else if (menu_type == 2) //ポーズ
        {
            //メニュー
            pausecnt = pause_.update();

        }
        else if (menu_type == 3) //ゲームオーバー
        {

        }
        else if (menu_type == 4) //ゲームクリア
        {

        }

        if (pausecnt == 2) //ゲームを続ける
        {
            pausecnt = 0;
            menu_type = 1;
        }
        else if (pausecnt == 3) //リセット
        {
            pausecnt = 0;
            menu_type = 1;
            return 3;
        }
        else if (pausecnt == 4) //メインメニュー
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

//描画
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

    //ポーズ
    if (menu_type == 2)
    {
        pause_.draw();
        pause_.cursordraw();
    }

    //ゲームクリア
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

    //ポーズ
    if (menu_type == 2)
    {
        pause_.draw();
        pause_.cursordraw();
    }


}

//破棄
void Game::destroy()
{
    start_.destroy();
    pause_.destroy();
    player_.destroy();
    ui_.destroy();
    mino_.destroy();
    clear_.destroy();
}