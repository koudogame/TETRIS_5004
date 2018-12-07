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
    //メンバ初期化
    if (!ui_.init()) { return false;}
    if (!player_.init()) { return false; }
    if (!mino_.init()) { return false; }

    return true;
}

//更新
bool Game::update()
{
    player_.update();
    ui_.update();
    pov_.update();
    mino_.update();

    return true;
}

//描画
void Game::draw()
{
    ui_.draw();
    ui_.inputdraw();
    mino_.draw();
    
}

//破棄
void Game::destroy()
{
    start_.destroy();
    field_.destroy();
    player_.destroy();
    ui_.destroy();
    start_.destroy();
    timelimit_.destroy();
}