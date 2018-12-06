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

    return true;
}

//更新
bool Game::update()
{
    player_.update();
    ui_.update();

    return true;
}

//描画
void Game::draw()
{
    ui_.draw();
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