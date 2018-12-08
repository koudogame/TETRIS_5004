#include "option.h"

bool Option::init()
{
    //�e�N�X�`���̓ǂݍ���
    if (!(texture_ = Texture::load(L"Tetris16_Option.png")))
    {

        Error::showDialog("Tetris16_Option.png�̓ǂݍ��݂Ɏ��s");

        //�G���[
        return false;
    }

    return true;
}

bool Option::update()
{
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    if (pad.buttons.start||state.LeftControl)
    {
        pstart = 1;
        return false;
    }
    else
    {
        pstart = 0;
    }

    if (pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter)
    {
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

void Option::destroy()
{

    SAFE_RELEASE(texture_);
}
