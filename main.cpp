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
#include"scene.h"
#include"credit.h"
#include"option.h"
#include"ranking.h"
#include"tetrismulti.h"
using namespace DirectX;
using namespace SimpleMath;

//�񋓑�
enum
{
    kSceneInit,         //�V�[���ω�������
    kSceneUpdate,       //�V�[���ω��X�V

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

    kResultUpdate,       // �Q�[���I��

    kOptionInit,         //�I�v�V����������
    kOptionUpdate,       //�I�v�V�����X�V

    kRankingInit,        //�����L���O������
    kRankingUpdate,      //�����L���O�X�V

    k4ptetrisInit,       //4�l�e�g���X������
    k4ptetrisUpdate      //4�l�e�g���X�X�V

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
    int work_no = kSceneInit;

    //�V�[���N���X�ϐ�
    Title title;
    Game game;
    Result result;
    Scene scene;
    Credit credit;
    Option option;
    UI ui;
    Ranking ranking;
    Start start;         
    Tetrismulti tetrismulti;


    int no = 0;
    int num = 0;
    bool oba = false;
    bool exit = false;
    bool bikerand = false;
    int gup = 0;

    ui.init();

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

                //�X�V����
                Pad::update();
                Key::update();

                //�V�[������
                switch (work_no)
                {
                case kSceneInit:
                    if (!scene.init())
                    {
                        //�G���[
                        PostQuitMessage(0);
                    }
                    work_no = kSceneUpdate;
                    break;
                case kSceneUpdate:
                    if (!scene.update())
                    {
                        work_no = kTitleInit;
                    }
                    break;
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
                    ui.update();
                    if (no == 2)
                    {
                        work_no = kGameInit;
                    }
                    else if (no == 3)
                    {
                        work_no = kRankingInit;
                    }
                    else if (no == 4)
                    {
                        work_no = kOptionInit;
                    }
                    else if (no == 5)
                    {
                        work_no = kCreditInit;
                    }
                    else if (no == 6)
                    {
                        work_no = k4ptetrisInit;
                    }
                    break;
                case kCreditInit:
                    if (!credit.init())
                    {
                        //�G���[
                        PostQuitMessage(0);
                    }
                    work_no = kCreditUpdate;
                    break;
                case kCreditUpdate:
                    ui.update();
                    if (!credit.update())
                    {
                        //�^�C�g���֖߂�
                        work_no = kTitleUpdate;
                        credit.destroy();
                    }
                    break;
                case kGameInit:
                    //�Q�[���N���X������
                    if (!game.init())
                    {
                        //�G���[
                        PostQuitMessage(0);
                    }

                    //���̏�����
                    work_no = kGameUpdate;
                    break;

                case kGameUpdate:
                     gup = game.update(0);

                    if (gup == 3) //���Z�b�g
                    {
                        game.destroy();
                        work_no = kGameInit;
                    }
                    else if (gup == 4) //�^�C�g����
                    {
                        game.destroy();
                        work_no = kTitleUpdate;
                    }
                     break;

                case kResultInit:
                    // ���̏���
                    work_no = kResultUpdate;
                    break;
                case kResultUpdate:
                    num = result.update(); //���U���g�X�V

                    // ���U���g��ʏI��
                    if (num == 1)
                    {
                        game.destroy(); //�Q�[�����̏������ׂĔj��
                        work_no = kTitleInit; //�^�C�g����
                    }
                    else if (num == 2)
                    {
                        exit = true;
                    }
                    break;
                case kOptionInit:
                    if (!option.init())
                    {
                        PostQuitMessage(0);
                    }
                    work_no = kOptionUpdate;
                    break;
                case kOptionUpdate:
                    ui.update();
                    if (!option.update())
                    {
                        option.destroy();
                        work_no = kTitleUpdate;
                    }
                    break;
                case kRankingInit:
                    if (!ranking.init())
                    {
                        //�G���[
                        PostQuitMessage(0);
                    }
                    work_no = kRankingUpdate;
                    break;
                case kRankingUpdate:
                    ui.update();
                    if (!ranking.update())
                    {
                        ranking.destroy();
                        work_no = kTitleUpdate;
                    }
                    break;
                case k4ptetrisInit:
                    if (!tetrismulti.init())
                    {
                        PostQuitMessage(0);
                    }
                    work_no = k4ptetrisUpdate;
                    break;
                case k4ptetrisUpdate:
                    if (!tetrismulti.update())
                    {
                        work_no = kResultInit;
                    }
                    break;
                }

                //��ʃN���A
                Direct3D::clear();

                //�X�v���C�g�`��J�n
                Sprite::begin();

                switch (work_no)
                {
                case kSceneUpdate:
                    scene.draw();
                    break;
                case kTitleUpdate:
                    title.draw();  //�^�C�g���w�i
                    ui.inputdraw(Title_);
                    title.cursordraw(); //�^�C�g���J�[�\��
                    break;
                case kStartUpdate:
                    start.draw();  //����
                    break;
                case kGameUpdate:
                    game.draw(); //�Q�[�������`��
                    break;
                case kHitSceneUpdate:
                    break;
                case kResultUpdate:
                    result.draw();       //�w�i
                    ui.inputdraw(result_option);
                    break;
                case kCreditUpdate:
                    credit.draw(); //�N���W�b�g�w�i
                    ui.inputdraw(rank_credit);
                    break;
                case kOptionUpdate:
                    option.draw(); //�I�v�V�����w�i
                    option.cursordraw();
                    option.opdraw();
                    ui.inputdraw(result_option); //���͏�ԕ\��
                    break;
                case kRankingUpdate:
                    ranking.draw();
                    ui.inputdraw(rank_credit);
                    break;
                case k4ptetrisUpdate:
                    tetrismulti.draw();
                    game.drawmulti();
                    ui.inputdraw(tetris_multi);
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
    scene.destroy();
    title.destroy();
    result.destroy();
    credit.destroy();
    game.destroy();
    ui.destroy();
    tetrismulti.destroy();
    
    option.destroy();
    ranking.destroy();
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