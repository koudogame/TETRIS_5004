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
bool Game::init(bool oba, int p2)
{


    //メンバ初期化

    if (oba)
    {

    }


    return true;
}

//更新
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

//描画
void Game::draw(bool oba)
{
    ui_.draw(); //背景
    field_.draw();
    field_.draw2();
    player_.draw(oba); //大場先生
    player_.draw2();//自転車
    ui_.partitiondraw(); //仕切り
    ui_.meterdraw(); //過失割合メーター
    timelimit_.draw(); //時間
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