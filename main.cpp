#include<WICTextureLoader.h>
#include<stdio.h>
#include<Windows.h>
#include<d3d11.h>
#include<ctime>
#include"direct3d.h"
#include"sprite.h"
#include"common.h"
#include"pad.h"
#include"key.h"
#include"game.h"
#include"title.h"
#include"adx.h"
#include "CueSheet_0.h"
using namespace DirectX;
using namespace SimpleMath;

//�񋓑�
enum
{
    kRatingInit,        //���[�e�B���O������
    kRatingUpdate,      //���[�e�B���O�X�V

    kTitleInit,         // �^�C�g����ʏ�����
    kTitleUpdate,       // �^�C�g����ʍX�V

    kStartInit,         //������ʏ�����
    kStartUpdate,       //������ʍX�V

    kGameInit,          // �Q�[����ʏ�����
    kGameUpdate,        // �Q�[����ʍX�V

    kHitSceneInit,      // ���̃V�[��������
    kHitSceneUpdate,    // ���̃V�[���X�V

    kResultInit,        // �Q�[�����U���g��ʏ�����
    kResultDraw,        // �Q�[�����U���g��ʕ`��

    kCreditInit,        //�N���W�b�g������
    kCreditUpdate,      //�N���W�b�g�X�V

    kResultUpdate       // �Q�[���I��

};


//�v���g�^�C�v�錾
LRESULT CALLBACK WinProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    //����������
    srand( time( NULL ) );

    //�E�B���h�E�N���X�̍쐬
    WNDCLASSEX wnd;
    ZeroMemory( &wnd, sizeof( WNDCLASSEX ) );
    wnd.cbSize = sizeof( WNDCLASSEX );                                                              //�\���̃T�C�Y
    wnd.style = CS_HREDRAW | CS_VREDRAW;                                                            //�X�^�C��
    wnd.hInstance = hInstance;                                                                      //�A�v���P�[�V�����C���X�^
    wnd.lpszClassName = "ClassName";                                                                //�N���X��
    wnd.hCursor = LoadCursor( NULL, IDC_ARROW );                                                    //�J�[�\���`��
    wnd.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wnd.lpfnWndProc = WinProc;                                                                      //�E�B���h�E�v���V�[�W���ւ̊֐��|�C���^

    //�o�^
    if( !RegisterClassEx( &wnd ) )
    {
        //�G���[
        return 0;
    }

    //�E�B���h�E�T�C�Y����
    RECT rect;
    rect.left = rect.top = 0L;
    rect.right = 1280L;
    rect.bottom = 720L;
    const DWORD style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    const DWORD ex_style = WS_EX_OVERLAPPEDWINDOW;
    AdjustWindowRectEx( &rect, style, false, ex_style );

    //�E�B���h�E�̍쐬
    const HWND hWnd = CreateWindowEx(
        ex_style,                                                                                   //�g���E�B���h�E�X�^�C��
        "ClassName",                                                                                //�N���X��
        "Title",                                                                                    //�E�B���h�E�^�C�g��
        style,                                                                                      //�E�B���h�E�^�C�g��
        CW_USEDEFAULT,                                                                              //�\�����WX
        CW_USEDEFAULT,                                                                              //�\�����WY
        rect.right - rect.left,                                                                     //�E�B���h�E����
        rect.bottom - rect.top,                                                                     //�E�B���h�E�c��
        NULL,                                                                                       //�e�E�B���h�E�ւ̃n���h��
        NULL,                                                                                       //���j���[�n���h��
        hInstance,                                                                                  //�A�v���P�[�V�����C���X�^���X
        NULL                                                                                        //�E�B���h�E�쐬�f�[�^
    );

    //NULL�`�F�b�N
    if( hWnd == NULL )
    {
        //�G���[
        return 0;
    }

    //direct3D�̏�����
    if( !Direct3D::init( hWnd ) )
    {
        //�G���[
        return 0;
    }

    //COM���C�u�����̏�����
    if( FAILED( CoInitializeEx( NULL, COINIT_MULTITHREADED ) ) )
    {
        //�G���[
        return 0;
    }

    //sprite�N���X�̏�����
    if( !Sprite::init() )
    {
        //�G���[
        return 0;
    }

    //common�N���X�̏�����
    if( !Common::init() )
    {
        //�G���[
        return 0;

    }

    //CRIADX�̏�����
    if( !Adx::init( "game.acf" ) )
    {
        //�G���[
        return 0;
    }

    //�T�E���h�̓ǂݍ���
    Adx::load( "CueSheet_0.acb", NULL );

    //CommonState�̍쐬
    CommonStates state( Direct3D::getDevice() );

    //�E�B���h�E�̕\��
    ShowWindow( hWnd, SW_SHOWNORMAL );

    //���C�����[�v
    MSG msg = { NULL };

    //���Ԍv��
    DWORD t1, t2, t3 = 0L, dt;
    t1 = timeGetTime();
    t2 = timeGetTime();

    //���݂̍�Ɣԍ�
    int work_no = kTitleInit;

    //�V�[���N���X�ϐ�
    Title title;
    Start start;
    Game game;
    Result result;

    int no = 0;
    int num = 0;
    int p2;
    bool oba = false;
    bool exit = false;
    bool bikerand = false;

    srand((unsigned)time(NULL));

    while (msg.message != WM_QUIT)
    {

        if (exit)
        {
            break;
        }

        //���b�Z�[�W����
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            //�t���[�����[�g����
            t1 = timeGetTime();                                                                     //���݂̎���
            dt = (t1 - t2) + t3;                                                                    //�O��̍X�V����̍������v�Z

            //��16�~���b�o�߂��Ă����珈�����s��
            if (dt > 16)
            {
                t2 = t1;                                                                            //���̎��Ԃ�O��̎��ԂƂ���
                t3 = dt % 16;                                                                       //�덷�����z��

                if (!bikerand)
                {
                    p2 = rand() % 3;
                    bikerand = true;
                }

                //�X�V����
                Pad::update();
                Key::update();
                Adx::update();

                //�V�[������
                switch (work_no)
                {
            
                case kTitleInit:

                    //�^�C�g���N���X������
                    if (!title.init())
                    {
                        //�G���[
                        PostQuitMessage(0);

                    }

                    //���̏�����
                    work_no = kTitleUpdate;
                    break;

                case kTitleUpdate:

                    no = title.update(); //�^�C�g���X�V

                    //�^�C�g���N���X�X�V����
                    if (no == 2)       // 2���Ԃ��Ă�����Q�[���J�n
                    {
                        work_no = kStartInit; //�ʏ탂�[�h�ŃQ�[���X�^�[�g
                    }
                    else if (no == 4)
                    {
                        oba = true; //��ꃂ�[�h�ŃQ�[���X�^�[�g
                        work_no = kStartInit;
                    }
                    else if (no == 3)  // 3���Ԃ��Ă�����N���W�b�g��
                    {
                        work_no = kCreditInit;
                    }
                    else if (no == 1)  //1���Ԃ��Ă�����Q�[���I��
                    {
                        exit = true;
                    }

                    break;

                case kStartInit:
					if (!start.init())
					{
						//�G���[
						PostQuitMessage(0);
					}

                    // ���̏�����
                    work_no = kStartUpdate;
                    break;
                case kStartUpdate:
                    if (!start.update())
                    {
						start.destroy(); //�X�^�[�g�j��
                        work_no = kGameInit;
                    }
                    break;
                case kGameInit:
                    //�Q�[���N���X������
                    if (!game.init(oba,p2))
                    {
                        //�G���[
                        PostQuitMessage(0);
                    }

                    if (oba)
                    {
                        Adx::stop();
                        Adx::play(1);
                    }
                    else
                    {
                        Adx::stop();
                        Adx::play(4);
                    }
                    //���̏�����
                    work_no = kGameUpdate;
                    break;

                case kGameUpdate:

                    if (!game.update(oba))
                    {
                        // ���̏�����
                        work_no = kHitSceneInit;
                    }
                    break;

                case kResultInit:
                    Adx::stop();
                    Adx::play(2);
                    // ���U���g�N���X������
                    if (!result.init(Player::get_mashpoint_1(), Player::get_mashpoint_2(),oba))
                    {
                        // �G���[
                        PostQuitMessage(0);
                    }
                    // ���̏���
                    work_no = kResultUpdate;
                    break;
                case kResultUpdate:
                    num = result.update(); //���U���g�X�V

                    // ���U���g��ʏI��
                    if (num == 1)
                    {
                        game.destroy(); //�Q�[�����̏������ׂĔj��
                        bikerand = false; //�o�C�N�̃����_���������J�n
                        work_no = kTitleInit; //�^�C�g����
                    }
                    else if (num == 2)
                    {
                        exit = true;
                    }

                    break;
                }

                //��ʃN���A
                Direct3D::clear();

                //�X�v���C�g�`��J�n
                Sprite::begin();

                switch (work_no)
                {
                case kTitleUpdate:
                    title.draw();  //�^�C�g���w�i
                    title.dpaddraw();  //�^�C�g���\��
                    title.buttondraw(); //�^�C�g��A�{�^��
                    break;
                case kStartUpdate:
                    start.draw();  //����
                    break;
                case kGameUpdate:
                    game.draw(oba); //�Q�[�������`��
                    break;
                case kHitSceneUpdate:
                    break;
                case kResultUpdate:
                    result.draw();       //�w�i
                    result.scoredraw1(); //1P�̃X�R�A�`��
                    result.scoredraw2(); //2P�̃X�R�A�`��
                    result.arrowdraw();  //���U���g���
                    break;

                }

                //�X�v���C�g�`��I��
                Sprite::end();

                //��ʍX�V              
                Direct3D::present();    //�`��X�V

            }
        }
    }
    
    //COM���C�u�����̊J��
    CoUninitialize();

    //�C���^�[�t�F�[�X�̉���i�m�ۂ������̋t�ɊJ�����Ă���)
    title.destroy();
    result.destroy();
    game.destroy();

    Common::destroy();
    Sprite::destroy();
    Direct3D::destroy();
    Adx::destroy();

    return 0;
}
// �R�[���o�b�N�֐�
LRESULT CALLBACK WinProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( Msg )
    {
    case WM_PAINT:
        hdc = BeginPaint( hWnd, &ps );
        EndPaint( hWnd, &ps );
        break;

    case WM_ACTIVATEAPP:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        break;

    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_KEYUP:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        break;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;

    case WM_KEYDOWN:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        switch( wParam )
        {

        case VK_ESCAPE:
            //ESC�������ꂽ�烋�[�v���I������
            PostMessage( hWnd, WM_CLOSE, 0, 0 );
            break;

        }
        break;
    }

    return DefWindowProc( hWnd, Msg, wParam, lParam );

}