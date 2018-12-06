#include "UI.h"

UI::UI()
{
    cnt = 0;
    carmeter=0;
    bicyclemeter = 0;
    texture_ = NULL;
    Mtexture_ = NULL;
    Ptexture_ = NULL;
}

bool UI::init()
{
    //���g���C���̏������Ɏg�p
    cnt = 0;
    carmeter = 0;
    bicyclemeter = 0;

    texture_ = Texture::load(L"field1.png");

    Mtexture_ = Texture::load(L"���[�^�[����.png");

    Ptexture_ = Texture::load(L"������.png");

    if (texture_ == NULL)
    {
        Error::showDialog("�K�C�h.png���ǂݍ��߂܂���");

        //�G���[
        return false;
    }

    if (Mtexture_ == NULL)
    {
        Error::showDialog("���[�^�[����.png���ǂݍ��߂܂���");

        //�G���[
        return false;
    }

    if (Ptexture_ == NULL)
    {
        Error::showDialog("�d�؂�.png���ǂݍ��߂܂���");

        //�G���[
        return false;
    }
    return true;
}

void UI::update()
{
    tmp++;
    const GamePad::State pad = Pad::getState();
    const GamePad::State pad2 = Pad::getState2();
    const Keyboard::State state = Key::getState();

    if (state.Enter || pad.buttons.a)
    {
       Bcnt++;
    }
    else
    {
        Bcnt = 0;
    }

    if (state.Space || pad2.buttons.a)
    {
       cnt++;
    }
    else
    {
        cnt = 0;
    }

    if (cnt == 1)
    {
        //�f�o�b�N�p
        carmeter += SPEED;
        bicyclemeter -= SPEED;
    }

    if (Bcnt == 1)
    {
        //�f�o�b�N�p
        bicyclemeter += SPEED;
        carmeter -= SPEED;
    }
    
    //�����Ԃ̉ߎ��������[�^�[�̌��x
    if (carmeter > 639)
    {
        carmeter = 639;
    }

    //�Ȃ����̉ߎ��������[�^�[�̌��x
    if (bicyclemeter > 639)
    {
        bicyclemeter = 639;
    }

}


void UI::draw()
{
    Sprite::draw(texture_, Vector2::Zero);
}

void UI::meterdraw()
{
    RECT rect;

    rect.top = 0;
    rect.left = 640+carmeter-bicyclemeter;
    rect.right = rect.left +1280;
    rect.bottom = rect.top + 100;

    Sprite::draw(Mtexture_, Vector2::Zero, &rect);
}

void UI::partitiondraw()
{
    Sprite::draw(Ptexture_, Vector2::Zero);
}

void UI::destroy()
{
    SAFE_RELEASE(texture_);
    SAFE_RELEASE(Mtexture_);
    SAFE_RELEASE(Ptexture_);
}