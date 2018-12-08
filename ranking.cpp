#include "ranking.h"

bool Ranking::init()
{
    //テクスチャの読み込み
    if (!(texture_ = Texture::load(L"Tetris13_Ranking.png")))
    {

        Error::showDialog("Tetris13_Ranking.pngの読み込みに失敗");

        //エラー
        return false;
    }
    return true;
}

bool Ranking::update()
{
    //ゲームパットの入力を取得
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    // キーボードの入力を取得
    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    //タイトルに戻る
    if (key_tracker.pressed.Enter || pad_tracker.a == GamePad::ButtonStateTracker::PRESSED)
    {
        return false;
    }

    return true;
}

void Ranking::draw()
{
    RECT trim;
    trim.top = 0;
    trim.left = 0;
    trim.bottom = trim.top + 720;
    trim.right = trim.left + 1280;

    Sprite::draw(texture_, Vector2::Zero, &trim);
}

void Ranking::destroy()
{
    SAFE_RELEASE(texture_);
}
