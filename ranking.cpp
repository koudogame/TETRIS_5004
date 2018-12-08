#include "ranking.h"

bool Ranking::init()
{
    //�e�N�X�`���̓ǂݍ���
    if (!(texture_ = Texture::load(L"Tetris13_Ranking.png")))
    {

        Error::showDialog("Tetris13_Ranking.png�̓ǂݍ��݂Ɏ��s");

        //�G���[
        return false;
    }
    return true;
}

bool Ranking::update()
{
    //�Q�[���p�b�g�̓��͂��擾
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    // �L�[�{�[�h�̓��͂��擾
    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    //�^�C�g���ɖ߂�
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
