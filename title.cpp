#include"title.h"

// �R���X�g���N�^
Title::Title()
{  
    texture_ = NULL;
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
    //�e�N�X�`���̓ǂݍ���
    if( !(texture_ = Texture::load( L"Tetris10_Title.png" )) )
    {

        Error::showDialog("�^�C�g��.png�̓ǂݍ��݂Ɏ��s");

        //�G���[
        return false;
    }

    return true;
}

//�X�V
int Title::update()
{
    //�Q�[���p�b�g�̓��͂��擾
    const GamePad::State pad = Pad::getState();
    const GamePad::State pad2 = Pad::getState2();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    // �L�[�{�[�h�̓��͂��擾
    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();


    // ���������ꂽ��
    if (key_tracker.pressed.Down || pad_tracker.dpadDown == GamePad::ButtonStateTracker::PRESSED)
    {
        menu++;
    }

    // �オ�����ꂽ��
    else if (key_tracker.pressed.Up || pad_tracker.dpadUp == GamePad::ButtonStateTracker::PRESSED)
    {
        menu--;
    }

    if (menu == 3 && key_tracker.pressed.Enter)
    {
        return 4; //�I�v�V����
    }

    if (menu == 4 && key_tracker.pressed.Enter)
    {
        return 5; //�N���W�b�g
    }

    // ���j���[�̃��[�v
    if (menu > 5)
    {
        menu = 0;
    }

    if (menu < 0)
    {
        menu = 5;
    }
    return 1;

}

//�`��
void Title::draw()
{

    RECT rect;

    rect.top = 0;
    rect.left = 0;
    rect.bottom = rect.top + 720;
    rect.right = rect.left + 1280;

    Sprite::draw(texture_, Vector2::Zero, &rect);
}

void Title::dpaddraw()
{
    RECT trim;

    trim.top = 725;
    trim.left = 5;
    trim.bottom = trim.top + 220;
    trim.right = trim.left + 220;


    Sprite::draw(texture_, Vector2(49,425), &trim);

}

void Title::buttondraw()
{

    RECT btrim;
    btrim.top = 463;
    btrim.left = 1536;
    btrim.bottom = btrim.top+129;
    btrim.right = btrim.left + 128;


    Sprite::draw(texture_, Vector2(1002, 519), &btrim);

}

void Title::cursordraw()
{
    RECT ctrim;

    ctrim.top = 947;
    ctrim.left = 1201;
    ctrim.bottom = ctrim.top + 35;
    ctrim.right = ctrim.left + 265;

    Sprite::draw(texture_, Vector2(505, 322+(menu*42)), &ctrim);

}

//�j��
void Title::destroy()
{
    //�e�N�X�`���̉��
    SAFE_RELEASE( texture_ );
}