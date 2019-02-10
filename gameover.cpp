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

int Gameover::update()
{
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    if (key_tracker.pressed.Up || pad_tracker.dpadUp == GamePad::ButtonStateTracker::PRESSED)
    {
        Adx::play(9);
        menu--;
    }
    if (key_tracker.pressed.Down || pad_tracker.dpadDown == GamePad::ButtonStateTracker::PRESSED)
    {
        Adx::play(9);

        menu++;
    }

    if (menu == 0 && (key_tracker.pressed.Enter || (pad_tracker.a == GamePad::ButtonStateTracker::PRESSED)))
    {
        Adx::play(10);

        //リトライ
        menu = 0;

        return 3;
    }

    if (menu == 1 && (key_tracker.pressed.Enter || (pad_tracker.a == GamePad::ButtonStateTracker::PRESSED)))
    {
        Adx::play(10);

        //メインメニュー
        menu = 0;

        return 4;
    }

    //メニューカーソルのループ
    if (menu > 1)
    {
        menu = 0;
    }
    if (menu < 0)
    {
        menu = 1;
    }

    return 1;

}

void Gameover::draw()
{
    //メニューウィンドウ

    RECT rect;

    rect.top = 0;
    rect.left = 1433 + 153*3;
    rect.bottom = rect.top + 153;
    rect.right = rect.left + 153;

    Sprite::draw(texture_, Vector2(558, 274), &rect);

    RECT trim;

    trim.top = 947;
    trim.left = 1186;
    trim.bottom = trim.top + 25;
    trim.right = trim.left + 15;

    Sprite::draw(texture_, Vector2(562, 323 + (menu * 25)), &trim);
}

void Gameover::destroy()
{
    SAFE_RELEASE(texture_);
}
