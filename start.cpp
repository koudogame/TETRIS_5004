#include"title.h"
#include"texture.h"
#include"sprite.h"
#include"pad.h"
#include"adx.h"
#include"key.h"
#include"start.h"

// �R���X�g���N�^
Start::Start()
{

    texture1_ = NULL;
    texture2_ = NULL;
    texture3_ = NULL;
    texture4_ = NULL;
    p1 = false;
    p2 = false;

}

//�f�X�g���N�^
Start::~Start()
{
}

//������
bool Start::init()
{
    //�e�N�X�`���̓ǂݍ���
    if( !(texture3_ = Texture::load( L"��������.png" ) )) //����������Ă��Ȃ�
    {
        //�G���[
        return false;
    }

    if (!(texture1_ = Texture::load(L"����1p.png"))) //1p�̂ݏ�������
    {
        //�G���[
        return false;
    }

    if (!(texture2_ = Texture::load(L"����2p.png"))) //2p�̂ݏ�������
    {
        //�G���[
        return false;
    }

    if (!(texture4_ = Texture::load(L"������������.png"))) //�S����������
    {
        //�G���[
        return false;
    }

    p1 = false;
	p2 = false;
    cnt = 0;

    return true;
}

//�X�V
bool Start::update()
{
	
	
		//�Q�[���p�b�g�̓��͂��擾
		const GamePad::State pad = Pad::getState();
		const GamePad::State pad2 = Pad::getState2();

		const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();
		const GamePad::ButtonStateTracker pad_tracker2 = Pad::getTracker2();

		// �L�[�{�[�h�̓��͂��擾
		const Keyboard::State state = Key::getState();
		const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

		if (!p1 && (pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter)) //1p�̏�������
		{
			Adx::play(9);
			p1 = true;

		}

		if (!p2 && (pad_tracker2.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Space)) //2p�̏�������
		{
			Adx::play(9);
			p2 = true;
		}
	

	if (p1&&p2) //���v���C���[�������������Ă�����J�E���g�X�^�[�g
	{
		cnt++;
	}

	if (cnt > 50&& p1&&p2) //�J�E���g��50�𒴂�����Q�[���X�^�[�g
	{
		return false;
	}

	return true;
}


//�`��
void Start::draw()
{
    if (p1&&p2)
    {
        Sprite::draw(texture4_, Vector2::Zero);
    }
    else if (p1 && !p2)
    {
        Sprite::draw(texture1_, Vector2::Zero);
    }
    else if (!p1&&p2)
    {
        Sprite::draw(texture2_, Vector2::Zero);
    }
    else
    {
        Sprite::draw(texture3_, Vector2::Zero);
    }

}

//�j��
void Start::destroy()
{

    //�e�N�X�`���̉��
    SAFE_RELEASE( texture1_ );
    SAFE_RELEASE( texture2_ );
    SAFE_RELEASE( texture3_ );
    SAFE_RELEASE( texture4_ );

}