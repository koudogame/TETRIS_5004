#include "clear.h"

Clear::Clear()
{
    texture_ = NULL;
}

bool Clear::init()
{

    texture_ = Texture::load(L"Tetris11_SingleT.png");

    if (texture_ == NULL)
    {
        Error::showDialog("Tetris11_SingleT.png���ǂݍ��߂܂���");

        //�G���[
        return false;
    }

    return true;
}

int Clear::update(int menu_type)
{

    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    //�I�[�����x���N���A
    if (mode == 0)
    {
        if (key_tracker.pressed.Enter||(pad_tracker.a || pad_tracker.b == GamePad::ButtonStateTracker::PRESSED))
        {
            Adx::play(9);
            //���̍��ڂ�
            mode = 3;
        }
    }
    else if (mode == 3) //���O����
    {
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

            //���g���C
            menu = 0;

            return 3;
        }

        if (menu == 1 && (key_tracker.pressed.Enter || (pad_tracker.a == GamePad::ButtonStateTracker::PRESSED)))
        {
            Adx::play(10);

            //���C�����j���[
            menu = 0;
            return 4;
        }

        //���j���[�J�[�\���̃��[�v
        if (menu > 1)
        {
            menu = 0;
        }
        if (menu < 0)
        {
            menu = 1;
        }

        return 2;
    }

    return 1;
}

//�N���A�E�B���h�E�̕`��
void Clear::draw()
{
    RECT rect;


    rect.top = 0;
    rect.left = 1433 + (153*mode);
    rect.bottom = rect.top + 153;
    rect.right = rect.left + 153;

    Sprite::draw(texture_, Vector2(558, 274), &rect);
}

//���j���[���J�[�\���̕`��
void Clear::cursordraw()
{
    RECT rect;

    rect.top = 947;
    rect.left = 1186;
    rect.bottom = rect.top + 25;
    rect.right = rect.left + 15;
    if (mode == 3)
    {
        Sprite::draw(texture_, Vector2(562, 323+(menu*25)), &rect);
    }
}

void Clear::destroy()
{
    SAFE_RELEASE(texture_);
}
