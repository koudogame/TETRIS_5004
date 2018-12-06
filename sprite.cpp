#include"sprite.h"
#include"direct3d.h"
#include"common.h"
#include"player.h"

// ���̂̐錾
SpriteBatch*  Sprite::sprite_;

//������
bool Sprite::init()
{
    //SpriteBatch�N���X�̃������m��
    sprite_ = new SpriteBatch( Direct3D::getContext() );

    //�������m�ۃ`�F�b�N
    if( !sprite_ )
    {
        return false;
    }

    return true;

}

    //�j��
void Sprite::destroy()
{
    //���������
    delete  sprite_;
}


    //�`��I��
void Sprite::end()
{
    sprite_->End();
}

//�`��J�n
void Sprite::begin()
{
    sprite_->Begin( SpriteSortMode_Deferred, Common::getState()->NonPremultiplied() );
}

void Sprite::draw(
    ID3D11ShaderResourceView* Texture,
    const Vector2& Position,
    const RECT* Rect,
    const float Rotation,
    const Vector2& Scale,
    const Vector2& Origin,
    const SpriteEffects Effect,
    const float Depth )
{
    sprite_->Draw(
        Texture,       // �e�N�X�`��
        Position,      // ���W
        Rect,          // �`��͈�
        Colors::White, // �J���[
        Rotation,      // ��]�l
        Origin,        //�A���J�[�|�C���g
        Scale,         //�g�k
        Effect,        //�G�t�F�N�g
        Depth );       //�[�x�l
}