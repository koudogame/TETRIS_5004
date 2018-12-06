#include"credit.h"
#include"texture.h"
#include"sprite.h"
#include"pad.h"
#include"keyboard.h"
#include"key.h"
#include"error.h"
#include"adx.h"

//初期化
bool Credit::init()
{
    //テクスチャの読み込み
    if (!(texture_ = Texture::load(L"Tetris17_Credit.png")))
    {
        //エラー
        Error::showDialog("クレジット画面がありません。");
        return false;
    }

    return true;
}

//更新
bool Credit::update()
{
    // パッド入力を取得
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();
    // キーボード入力を取得
    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();


    if( pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter )
    {
        return false;
    }

    return true;
}

//描画
void Credit::draw()
{
    Sprite::draw(texture_, Vector2::Zero);
}

void Credit::buttondraw()
{

    RECT btrim;
    btrim.top = 463;
    btrim.left = 1536;
    btrim.bottom = btrim.top + 129;
    btrim.right = btrim.left + 128;


    Sprite::draw(texture_, Vector2(1002, 519), &btrim);
}

void Credit::destroy()
{
    //テクスチャの開放
    SAFE_RELEASE( texture_ );
    SAFE_RELEASE( Ctexture_ );
}