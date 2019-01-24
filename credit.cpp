#include"credit.h"
#include"texture.h"
#include"sprite.h"
#include"pad.h"
#include"keyboard.h"
#include"key.h"
#include"error.h"
#include"adx.h"

//������
bool Credit::init()
{
    //�e�N�X�`���̓ǂݍ���
    if (!(texture_ = Texture::load(L"Tetris17_Credit.png")))
    {
        //�G���[
        Error::showDialog("�N���W�b�g��ʂ�����܂���B");
        return false;
    }

    return true;
}

//�X�V
bool Credit::update()
{
    // �p�b�h���͂��擾
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();
    // �L�[�{�[�h���͂��擾
    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();


    if( pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter )
    {
        Adx::play(10);

        return false;
    }

    return true;
}

//�`��
void Credit::draw()
{
    Sprite::draw(texture_, Vector2::Zero);
}

void Credit::namedraw()
{
    RECT rect;

    for (int i = 0; i < 13; i++)
    {
        rect.top = 961;
        rect.left = 160-16+(name[i]*16);
        rect.bottom = rect.top + 21;
        rect.right = rect.left + 16;
        if (name[i] != 0)
        {
            Sprite::draw(texture_, Vector2(530+(i*16), 107), &rect);
        }
    }
}

void Credit::datedraw()
{
    RECT rect;

    for (int i = 0; i < 11; i++)
    {
        rect.top = 961;
        rect.left = 0 + (creation_date[i] * 16);
        rect.bottom = rect.top + 21;
        rect.right = rect.left + 16;
        if (creation_date[i] != 100)
        {
            Sprite::draw(texture_, Vector2(555 + (i * 16), 620), &rect);
        }
    }
}

void Credit::destroy()
{
    //�e�N�X�`���̊J��
    SAFE_RELEASE( texture_ );
}