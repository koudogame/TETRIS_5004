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
    if (!(texture_ = Texture::load(L"credit.png")))
    {
        //�G���[
        Error::showDialog("���U���g��ʂ�����܂���B");
        return false;
    }

    if (!(Ctexture_ = Texture::load(L"���.png")))
    {
        //�G���[
        Error::showDialog("���.png������܂���B");
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

    cnt++;

    if( pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter )
    {
        Adx::play( 6 );
        Sleep(550);
        return false;
    }

    return true;
}

//�`��
void Credit::draw()
{
    Sprite::draw(texture_, Vector2::Zero);
}

void Credit::arrowdraw()
{
    RECT rect;

    const GamePad::State pad = Pad::getState();
    const Keyboard::State state = Key::getState();

    rect.top = 200;
    rect.left = 0;
    rect.right = rect.left + 200;
    rect.bottom = rect.top + 200;

    Sprite::draw(Ctexture_, Vector2(820.0F, 500.0F), &rect);


}

void Credit::destroy()
{
    //�e�N�X�`���̊J��
    SAFE_RELEASE( texture_ );
    SAFE_RELEASE( Ctexture_ );
}