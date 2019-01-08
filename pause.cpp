#include "pause.h"

Pause::Pause()
{
    texture_ = NULL;
}

bool Pause::init()
{
    texture_ = Texture::load(L"Tetris11_SingleT.png");

    if (texture_ == NULL)
    {
        Error::showDialog("Tetris11_singleT.pngが読み込めません");
   
        //エラー
        return false;

    }

    return true;
}

int Pause::update()
{

    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();


    if (pad_tracker.dpadDown == GamePad::ButtonStateTracker::PRESSED)
    {
        menucnt++;
    }
    if (pad_tracker.dpadUp == GamePad::ButtonStateTracker::PRESSED)
    {
        menucnt--;
    }

    if (menucnt < 0)
    {
        menucnt = 2;
    }
    else if (menucnt > 2)
    {
        menucnt = 0;
    }

    //ゲームを続ける
    if (menucnt == 0 && (pad_tracker.a == GamePad::ButtonStateTracker::PRESSED))
    {
        return 2;
    }
    //リセット
    else if (menucnt == 1 && (pad_tracker.a == GamePad::ButtonStateTracker::PRESSED))
    {
        return 3;
    }
    //メインメニューに戻る
    else if (menucnt == 2 && (pad_tracker.a == GamePad::ButtonStateTracker::PRESSED))
    {
        return 4;
    }



    return 1;
}

void Pause::draw()
{

    RECT rect;
    rect.top = 306;
    rect.left = 1280;
    rect.bottom = rect.top + 155;
    rect.right = rect.left + 153;

    Sprite::draw(texture_, Vector2(558, 274), &rect);

}

void Pause::cursordraw()
{

    RECT rect;

    rect.top = 947;
    rect.left = 1186;
    rect.bottom = rect.top + 25;
    rect.right = rect.left + 15;

    Sprite::draw(texture_, Vector2(562, 320 + (24 * menucnt)), &rect); //難易度


}

void Pause::destroy()
{

    SAFE_RELEASE(texture_);

}
