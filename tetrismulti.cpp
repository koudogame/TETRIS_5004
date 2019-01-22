#include "tetrismulti.h"

Tetrismulti::Tetrismulti()
{
    texture_ = NULL;
}

bool Tetrismulti::init()
{

    texture_ = Texture::load(L"Tetris14_Versus.png");


    if (texture_ == NULL)
    {
        Error::showDialog("Tetris11_Versus.png���ǂݍ��߂܂���");

        //�G���[
        return false;
    }

    return true;
}

int Tetrismulti::update()
{
    for (int i = 0; i < 4; i++)
    {
        mino_.update(i);
    }



    return 1;
}

//�w�i
void Tetrismulti::draw()
{
    for (int i = 1; i < 5; i++)
    {
        mino_.draw(i); //���������
        ui_.Hiddendraw(); //�B��
        mino_.maindraw(i); //�ςݏグ
        mino_.nextdraw(i); //�l�N�X�g
        mino_.holddraw(i); //�z�[���h
    }


    RECT rect;
    rect.top = 0;
    rect.left = 0;
    rect.bottom = rect.top + 720;
    rect.right = rect.left + 1280;

    Sprite::draw(texture_,Vector2::Zero, &rect);

}

void Tetrismulti::destroy()
{
    SAFE_RELEASE(texture_);
}
