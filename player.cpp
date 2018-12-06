#include"player.h"
#include"texture.h"
#include"sprite.h"
#include"pad.h"
#include"key.h"

#include"adx.h"

Player player;
// ���̂̐錾
int Player::mash_point1_;
int Player::mash_point2_;

enum
{
    kDown,
    kUp,
    kRight,
    kLeft,
};

// �A�N�V�����ԍ�
enum Action
{
    animation1,
    animation2,
    animation3,
};

enum Motion
{
    normal,
    turn,
};

// �R���X�g���N�^
Player::Player()
{
    //�����o�ϐ�������
    position_.x = static_cast<float>(0.0F);
    position_.y = static_cast<float>(600.0F - 196.0F);

    // �A�j���[�V�����֌W
    animation_no_ = animation1;
    animation_pattern_ = normal;                                                                                                                                                                                   // �A�j���[�V�����ԍ�
    animation_counter_ = 0;

    // �A�N�V�����֘A
    action_flag_ = false;
    action_count_ = 0;


    // �����o�ϐ�������
    texture_1 = NULL;
    texture_2 = NULL;
}


//�f�X�g���N�^
Player::~Player()
{
}

//������
bool Player::init( )
{
    //�e�N�X�`���̓ǂݍ���

    //texture_1 = Texture::load();

    //NULL�`�F�b�N
    if( texture_1 == NULL )
    {

        Error::showDialog( "texture_1���ǂݍ��߂܂���" );

        //�G���[
        return false;
    }

    return true;

}

//�X�V����
void Player::update()
{

        // �A�j���[�V��������
        animation_no_++;

        // �A�j���[�V�����ԍ������Z�b�g����
        if (animation_no_ > animation3)
        {
            animation_no_ = animation1;
        }

        // �����_���ő��搶�̌�����ύX
        if (int pattern_manager = animation_counter_ % 200)
        {
            if (pattern_manager <= 130
                )
            {
                animation_pattern_ = normal;
            }
            else
            {
                animation_pattern_ = turn;
            }
        }
   

    // 1P�R���g���[���̓��͂��擾
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    // 2P�R���g���[���̓��͂��擾
    const GamePad::State pad2 = Pad::getState2();
    const GamePad::ButtonStateTracker pad_tracker2 = Pad::getTracker2();

    // �L�[�{�[�h�̓��͂��擾
    const Keyboard::State key = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    // �A�Ő������Z����
    if( pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter )
    {
        mash_point1_++;
	
			Adx::play(5);
    }

    if( pad_tracker2.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Space )
    {
        mash_point2_++;
    }

    // �A�j���[�V�����J�E���^�����Z
    animation_counter_++;

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
    SAFE_RELEASE( texture_2 );
}