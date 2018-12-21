#include "option.h"

bool Option::init()
{
    //テクスチャの読み込み
    if (!(texture_ = Texture::load(L"Tetris16_Option.png")))
    {

        Error::showDialog("Tetris16_Option.pngの読み込みに失敗");

        //エラー
        return false;
    }

    opmenu = 0;
    return true;
}

bool Option::update()
{
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    //メニューカーソル上下
    if (key_tracker.pressed.Up || pad_tracker.dpadUp == GamePad::ButtonStateTracker::PRESSED)
    {
        //メニューカーソルを上に上げる
        opmenu--;
    }
    if (key_tracker.pressed.Down || pad_tracker.dpadDown == GamePad::ButtonStateTracker::PRESSED)
    {
        //メニューカーソルを下に下げる
        opmenu++;
    }

    //難易度選択
    if (opmenu == 0 && state.Left)
    {
        difficulty = 0;
    }
    else if (opmenu == 0 && state.Right)
    {
        difficulty = 1;
    }

    //ホールド
    if (opmenu == 1 && state.Left)
    {
        hold = 0;
    }
    else if (opmenu == 1 && state.Right)
    {
        hold = 1;
    }

    //ネクスト
    if (opmenu == 2 && (key_tracker.pressed.Left || pad_tracker.dpadLeft == GamePad::ButtonStateTracker::PRESSED))
    {
        next--;
    }
    else if (opmenu == 2 && (key_tracker.pressed.Right || pad_tracker.dpadRight == GamePad::ButtonStateTracker::PRESSED))
    {
        next++;
    }

    //制限
    if (next > 3)
    {
        next = 3;
    }
    else if (next < 0)
    {
        next = 0;
    }

    //Hidden
    if (opmenu == 3 && state.Left)
    {
        hidden = 0;
    }
    else if (opmenu == 3 && state.Right)
    {
        hidden = 1;
    }

    //VS
    if (opmenu == 4 && state.Left)
    {
        vs = 0;
    }
    else if (opmenu == 4 && state.Right)
    {
        vs = 1;
    }

    //Reverse
    if (opmenu == 5 && state.Left)
    {
        reverse = 0;
    }
    else if (opmenu == 5 && state.Right)
    {
        reverse = 1;
    }

    //score
    if (opmenu == 6 && state.Left)
    {
        score = 0;
    }
    else if (opmenu == 6 && state.Right)
    {
        score = 1;
    }

    //EXIT
    if (opmenu == 7 && (key_tracker.pressed.Enter || pad_tracker.a == GamePad::ButtonStateTracker::PRESSED))
    {
        pstart = 1;
        return false;
    }
    else
    {
        pstart = 0;
    }

    //カーソルループ
    if (opmenu > 7)
    {
        opmenu = 0;
    }
    else if (opmenu < 0)
    {
        opmenu = 7;
    }

    return true;
}

void Option::draw()
{
    RECT rect;
    rect.top = 0;
    rect.left = 0;
    rect.bottom = rect.top + 720;
    rect.right = rect.left + 1280;

    Sprite::draw(texture_, Vector2::Zero);
}

//選択カーソルの描画
void Option::cursordraw()
{
    RECT trim;

    trim.top = 957;
    trim.left = 1550;
    trim.bottom = trim.top + 67.5;
    trim.right = trim.left + 498;

    Sprite::draw(texture_, Vector2(400, 108+(opmenu*65)+(opmenu*3)), &trim);

}

void Option::opdraw()
{
    RECT rect;

    rect.top = 950;
    rect.left = 1188;
    rect.bottom = rect.top + 20;
    rect.right = rect.left + 12;

    Sprite::draw(texture_, Vector2(606+(149*difficulty),133), &rect); //難易度
    Sprite::draw(texture_, Vector2(646+(108*hold),201), &rect); //ホールド
    Sprite::draw(texture_, Vector2(597+(69*next),269), &rect); //ネクスト
    Sprite::draw(texture_, Vector2(646+(108*hidden),337), &rect); //
    Sprite::draw(texture_, Vector2(646+(108*vs),405), &rect); //VS
    Sprite::draw(texture_, Vector2(646+(108*reverse),473), &rect); //リバーススクリーン
    Sprite::draw(texture_, Vector2(606+(149*score),473+68), &rect); //スコアリセット
}

void Option::destroy()
{
    SAFE_RELEASE(texture_);
}
