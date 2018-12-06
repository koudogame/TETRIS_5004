#include"title.h"

// �R���X�g���N�^
Title::Title()
{  
    texture_ = NULL;
    texture2_ = NULL;
    texture3_ = NULL;
    oba = false;
}

// ���艹�҂�����
const int wait = 550;

//�f�X�g���N�^
Title::~Title()
{
}

//������
bool Title::init()
{
    menu = 0;
    oba = false;
    cnt = 0;
    //�e�N�X�`���̓ǂݍ���
    if( !(texture_ = Texture::load( L"�W���^�C�g��.png" )) )
    {

        Error::showDialog("�W���^�C�g��.png�̓ǂݍ��݂Ɏ��s");

        //�G���[
        return false;
    }

    //�e�N�X�`���̓ǂݍ���
    if (!(texture2_ = Texture::load(L"�^�C�g�����.png")))
    {

        Error::showDialog("�^�C�g��.png�̓ǂݍ��݂Ɏ��s");

        //�G���[
        return false;
    }
    // �e�N�X�`���̓ǂݍ���
    if( !(texture3_ = Texture::load( L"���搶�^�C�g��.png" )) )
    {

        Error::showDialog( "���搶�^�C�g��.png�̓ǂݍ��݂Ɏ��s" );

        //�G���[
        return false;
    }

    return true;
}

//�X�V
int Title::update()
{
    tmp = oba; //�O�̃t���[���̃t���O��Ԃ��擾

    //�Q�[���p�b�g�̓��͂��擾
    const GamePad::State pad = Pad::getState();
    const GamePad::State pad2 = Pad::getState2();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    // �L�[�{�[�h�̓��͂��擾
    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    if (!oba)
    {
        if (pad.dpad.up&&pad.dpad.left&&pad2.dpad.right&&pad2.dpad.down)
        {
            cnt++;
        }
        else
        {
            cnt = 0;
        }

        if (cnt > 50)
        {
            oba = true;
        }
    }

    if (state.F1) //��ꃂ�[�h����
    {
        oba = false;
    }

    if (tmp!=oba) //���[�h�؂�ւ���
    {
        if( oba )
        {
            Adx::stop();
            Adx::play( 0 );
            Adx::play( 5 );
        }
        else
        {
            Adx::stop();
            Adx::play( 3 );
        }
    }

    // ���������ꂽ��
    if (key_tracker.pressed.Down || pad_tracker.dpadDown == GamePad::ButtonStateTracker::PRESSED)
    {
        menu++;
		Adx::play(10);
    }

    // �オ�����ꂽ��
    else if (key_tracker.pressed.Up || pad_tracker.dpadUp == GamePad::ButtonStateTracker::PRESSED)
    {
        menu--;
		Adx::play(10);
    }

    // ���j���[�̃��[�v
    if (menu > 2)
    {
        menu = 0;
    }

    if (menu < 0)
    {
        menu = 2;
    }

    if (oba&&menu == 0 && (pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter))  //�Q�[���X�^�[�g(��ꃂ�[�h)
    {
        Adx::play(6);
        Sleep(wait);
        return 4;
    }
    if (menu == 0 && (pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter))  //�Q�[���X�^�[�g(�ʏ�)
    {
        Adx::play(6);
        Sleep(wait);
        return 2;
    }
    if (menu == 1 && (pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter))   //�N���W�b�g
    {
        Adx::play(6);
        Sleep(wait);
        return 3;
    }
    if (menu == 2 && (pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter)) //exit
    {
        Adx::play(6);
        Sleep(wait);
        return 1;
    }

    return 6;

}

//�`��
void Title::draw()
{
    if( oba )
    {
        Sprite::draw( texture3_, Vector2::Zero );
    }
    else
    {
        Sprite::draw( texture_, Vector2::Zero );
    }
}

void Title::adraw()
{
    RECT rect;

    if( menu == 0 )
    {
        rect.top = 0;
        rect.left = 0;
        rect.right = rect.left + 200;
        rect.bottom = rect.top + 200;
    }
    else if( menu == 1 )
    {
        rect.top = 200;
        rect.left = 0;
        rect.right = rect.left + 200;
        rect.bottom = rect.top + 200;
    }
    else if( menu == 2 )
    {
        rect.top = 400;
        rect.left = 0;
        rect.right = rect.left + 200;
        rect.bottom = rect.top + 200;
    }
    Sprite::draw( texture2_, Vector2( 370.0F, 360.0F ), &rect );
}

//�j��
void Title::destroy()
{
    //�e�N�X�`���̉��
    SAFE_RELEASE( texture_ );
    SAFE_RELEASE( texture2_ );
    SAFE_RELEASE( texture3_ );
}