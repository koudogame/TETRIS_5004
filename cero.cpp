#include "cero.h"
#include<Windows.h>
#include "pad.h"
#include "key.h"
bool Cero::init()
{

    texture_ = Texture::load(L"レーティング.png");

    if (texture_ == NULL)
    {
        Error::showDialog("texture_が読み込めません");

        return false;
    }

    return true;
}

bool Cero::update()
{
    cnt++;
    // コントローラ入力を取得
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    // キーボード入力を取得
    const Keyboard::State key = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();


    if( pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter )
    {
        return false;
    }

    if (cnt > 320)
    {
        cnt = 0;
        return false;
    }

    return true;
}

void Cero::draw()
{
    //描画
    Sprite::draw(texture_, Vector2::Zero);
}

void Cero::destroy()
{
    //破棄
    SAFE_RELEASE(texture_);
}
