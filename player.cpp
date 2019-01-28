#include"player.h"
#include"texture.h"
#include"sprite.h"
#include"pad.h"
#include"key.h"
#include"adx.h"

Player player;

// �R���X�g���N�^
Player::Player()
{
    // �����o�ϐ�������
    texture_1 = NULL;
}


//�f�X�g���N�^
Player::~Player()
{
}

//������
bool Player::init( )
{
    //�e�N�X�`���̓ǂݍ���

    texture_1 = Texture::load(L"Tetris11_SingleT.png");

    //NULL�`�F�b�N
    if( texture_1 == NULL )
    {

        Error::showDialog( "Tetris11_SingleT.png���ǂݍ��߂܂���" );

        //�G���[
        return false;
    }

    return true;

}

//�X�V����
void Player::update()
{

    // 1P�R���g���[���̓��͂��擾
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    // 2P�R���g���[���̓��͂��擾
    const GamePad::State pad2 = Pad::getState2();
    const GamePad::ButtonStateTracker pad_tracker2 = Pad::getTracker2();

    // �L�[�{�[�h�̓��͂��擾
    const Keyboard::State key = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

}

//�`��
void Player::draw()  //��
{
    RECT rect;

  
        // �`��͈͂̐ݒ�
        rect.top = animation_pattern_ * 196L;
        rect.left = animation_no_ * 600L;
        rect.right = rect.left + 600L;
        rect.bottom = rect.top + 196L;

        // �`��
        Sprite::draw(texture_1, position_, &rect);

}

void Player::draw2()  //�`����
{
    // �`��͈͂̐ݒ�
    RECT rect;
    rect.top =0L;
    rect.left = 0L;
    rect.right = rect.left + 210L;
    rect.bottom = rect.top + 301L;

    Vector2 scale( 0.5F, 0.5F );
    Vector2 origin( 0.0F, 0.0F );

    // �`��
    Sprite::draw( texture_2, Vector2( 900.0F, 390.0F ), &rect );
}


//�j��
void Player::destroy()
{
    SAFE_RELEASE( texture_1 );
}