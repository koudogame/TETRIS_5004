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
    if (!(texture_ = Texture::load(L"credit.png")))
    {
        //エラー
        Error::showDialog("リザルト画面がありません。");
        return false;
    }

    if (!(Ctexture_ = Texture::load(L"矢印.png")))
    {
        //エラー
        Error::showDialog("矢印.pngがありません。");
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

    cnt++;

    if( pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter )
    {
        Adx::play( 6 );
        Sleep(550);
        return false;
    }

    return true;
}

//描画
void Credit::draw()
{
    Sprite::draw(texture_, Vector2::Zero);
}

void Credit::arrowdraw()
{
    RECT rect;

    const GamePad::State pad = Pad::getState();
    const Keyboard::State state = Key::getState();

    rect.top = 200;
    rect.left = 0;
    rect.right = rect.left + 200;
    rect.bottom = rect.top + 200;

    Sprite::draw(Ctexture_, Vector2(820.0F, 500.0F), &rect);


}

void Credit::destroy()
{
    //テクスチャの開放
    SAFE_RELEASE( texture_ );
    SAFE_RELEASE( Ctexture_ );
}