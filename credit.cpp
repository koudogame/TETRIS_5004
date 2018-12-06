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
        return false;
    }

    return true;
}

//�`��
void Credit::draw()
{
    Sprite::draw(texture_, Vector2::Zero);
}

void Credit::buttondraw()
{

    RECT btrim;
    btrim.top = 463;
    btrim.left = 1536;
    btrim.bottom = btrim.top + 129;
    btrim.right = btrim.left + 128;


    Sprite::draw(texture_, Vector2(1002, 519), &btrim);
}

void Credit::destroy()
{
    //�e�N�X�`���̊J��
    SAFE_RELEASE( texture_ );
    SAFE_RELEASE( Ctexture_ );
}