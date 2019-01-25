#include "gameover.h"

Gameover::Gameover()
{
    texture_ = NULL;
}

bool Gameover::init()
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

void Gameover::update()
{
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    if (key_tracker.pressed.A || pad_tracker.a == GamePad::ButtonStateTracker::PRESSED)
    {
        menucnt++;
    }

}

void Gameover::draw()
{
    //メニューウィンドウ
    RECT rect;
    rect.top = 0;
    rect.left = 1739-153;
    rect.bottom = rect.top + 153;
    rect.right = rect.left + 153;

    //ランク
    RECT rank;
    rank.top = 961;
    rank.left = 0;
    rank.right = rank.left + 16;
    rank.bottom = rank.top + 21;

    Sprite::draw(texture_, Vector2(558, 274), &rect);
    Sprite::draw(texture_, Vector2(573, 336), &rank); //ランク

}

void Gameover::scoredraw(int score)
{

}

void Gameover::rankdraw(int rank)
{
}

void Gameover::destroy()
{
    SAFE_RELEASE(texture_);
}
