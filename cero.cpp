#include "cero.h"
#include<Windows.h>
#include "pad.h"
#include "key.h"
bool Cero::init()
{

    texture_ = Texture::load(L"���[�e�B���O.png");

    if (texture_ == NULL)
    {
        Error::showDialog("texture_���ǂݍ��߂܂���");

        return false;
    }

    return true;
}

bool Cero::update()
{
    cnt++;
    // �R���g���[�����͂��擾
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    // �L�[�{�[�h���͂��擾
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
    //�`��
    Sprite::draw(texture_, Vector2::Zero);
}

void Cero::destroy()
{
    //�j��
    SAFE_RELEASE(texture_);
}
