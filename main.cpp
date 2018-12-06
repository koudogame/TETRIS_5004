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

//列挙体
enum
{
    kRatingInit,        //レーティング初期化
    kRatingUpdate,      //レーティング更新

    kTitleInit,         // タイトル画面初期化
    kTitleUpdate,       // タイトル画面更新

    kStartInit,         //説明画面初期化
    kStartUpdate,       //説明画面更新

    kGameInit,          // ゲーム画面初期化
    kGameUpdate,        // ゲーム画面更新

    kHitSceneInit,      // 事故シーン初期化
    kHitSceneUpdate,    // 事故シーン更新

    kResultInit,        // ゲームリザルト画面初期化
    kResultDraw,        // ゲームリザルト画面描画

    kCreditInit,        //クレジット初期化
    kCreditUpdate,      //クレジット更新

    kResultUpdate       // ゲーム終了

};


//プロトタイプ宣言
LRESULT CALLBACK WinProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    //乱数初期化
    srand( time( NULL ) );

    //ウィンドウクラスの作成
    WNDCLASSEX wnd;
    ZeroMemory( &wnd, sizeof( WNDCLASSEX ) );
    wnd.cbSize = sizeof( WNDCLASSEX );                                                              //構造体サイズ
    wnd.style = CS_HREDRAW | CS_VREDRAW;                                                            //スタイル
    wnd.hInstance = hInstance;                                                                      //アプリケーションインスタ
    wnd.lpszClassName = "ClassName";                                                                //クラス名
    wnd.hCursor = LoadCursor( NULL, IDC_ARROW );                                                    //カーソル形状
    wnd.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wnd.lpfnWndProc = WinProc;                                                                      //ウィンドウプロシージャへの関数ポインタ

    //登録
    if( !RegisterClassEx( &wnd ) )
    {
        //エラー
        return 0;
    }

    //ウィンドウサイズ決定
    RECT rect;
    rect.left = rect.top = 0L;
    rect.right = 1280L;
    rect.bottom = 720L;
    const DWORD style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    const DWORD ex_style = WS_EX_OVERLAPPEDWINDOW;
    AdjustWindowRectEx( &rect, style, false, ex_style );

    //ウィンドウの作成
    const HWND hWnd = CreateWindowEx(
        ex_style,                                                                                   //拡張ウィンドウスタイル
        "ClassName",                                                                                //クラス名
        "Title",                                                                                    //ウィンドウタイトル
        style,                                                                                      //ウィンドウタイトル
        CW_USEDEFAULT,                                                                              //表示座標X
        CW_USEDEFAULT,                                                                              //表示座標Y
        rect.right - rect.left,                                                                     //ウィンドウ横幅
        rect.bottom - rect.top,                                                                     //ウィンドウ縦幅
        NULL,                                                                                       //親ウィンドウへのハンドル
        NULL,                                                                                       //メニューハンドル
        hInstance,                                                                                  //アプリケーションインスタンス
        NULL                                                                                        //ウィンドウ作成データ
    );

    //NULLチェック
    if( hWnd == NULL )
    {
        //エラー
        return 0;
    }

    //direct3Dの初期化
    if( !Direct3D::init( hWnd ) )
    {
        //エラー
        return 0;
    }

    //COMライブラリの初期化
    if( FAILED( CoInitializeEx( NULL, COINIT_MULTITHREADED ) ) )
    {
        //エラー
        return 0;
    }

    //spriteクラスの初期化
    if( !Sprite::init() )
    {
        //エラー
        return 0;
    }

    //commonクラスの初期化
    if( !Common::init() )
    {
        //エラー
        return 0;

    }

    //CRIADXの初期化
    if( !Adx::init( "game.acf" ) )
    {
        //エラー
        return 0;
    }

    //サウンドの読み込み
    Adx::load( "CueSheet_0.acb", NULL );

    //CommonStateの作成
    CommonStates state( Direct3D::getDevice() );

    //ウィンドウの表示
    ShowWindow( hWnd, SW_SHOWNORMAL );

    //メインループ
    MSG msg = { NULL };

    //時間計測
    DWORD t1, t2, t3 = 0L, dt;
    t1 = timeGetTime();
    t2 = timeGetTime();

    //現在の作業番号
    int work_no = kTitleInit;

    //シーンクラス変数
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

        //メッセージ処理
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            //フレームレート制御
            t1 = timeGetTime();                                                                     //現在の時間
            dt = (t1 - t2) + t3;                                                                    //前回の更新からの差分を計算

            //約16ミリ秒経過していたら処理を行う
            if (dt > 16)
            {
                t2 = t1;                                                                            //今の時間を前回の時間とする
                t3 = dt % 16;                                                                       //誤差分を吸収

                if (!bikerand)
                {
                    p2 = rand() % 3;
                    bikerand = true;
                }

                //更新処理
                Pad::update();
                Key::update();
                Adx::update();

                //シーン処理
                switch (work_no)
                {
            
                case kTitleInit:

                    //タイトルクラス初期化
                    if (!title.init())
                    {
                        //エラー
                        PostQuitMessage(0);

                    }

                    //次の処理へ
                    work_no = kTitleUpdate;
                    break;

                case kTitleUpdate:

                    no = title.update(); //タイトル更新

                    //タイトルクラス更新処理
                    if (no == 2)       // 2が返ってきたらゲーム開始
                    {
                        work_no = kStartInit; //通常モードでゲームスタート
                    }
                    else if (no == 4)
                    {
                        oba = true; //大場モードでゲームスタート
                        work_no = kStartInit;
                    }
                    else if (no == 3)  // 3が返ってきたらクレジットへ
                    {
                        work_no = kCreditInit;
                    }
                    else if (no == 1)  //1が返ってきたらゲーム終了
                    {
                        exit = true;
                    }

                    break;

                case kStartInit:
					if (!start.init())
					{
						//エラー
						PostQuitMessage(0);
					}

                    // つぎの処理へ
                    work_no = kStartUpdate;
                    break;
                case kStartUpdate:
                    if (!start.update())
                    {
						start.destroy(); //スタート破棄
                        work_no = kGameInit;
                    }
                    break;
                case kGameInit:
                    //ゲームクラス初期化
                    if (!game.init(oba,p2))
                    {
                        //エラー
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
                    //次の処理へ
                    work_no = kGameUpdate;
                    break;

                case kGameUpdate:

                    if (!game.update(oba))
                    {
                        // 次の処理へ
                        work_no = kHitSceneInit;
                    }
                    break;

                case kResultInit:
                    Adx::stop();
                    Adx::play(2);
                    // リザルトクラス初期化
                    if (!result.init(Player::get_mashpoint_1(), Player::get_mashpoint_2(),oba))
                    {
                        // エラー
                        PostQuitMessage(0);
                    }
                    // 次の処理
                    work_no = kResultUpdate;
                    break;
                case kResultUpdate:
                    num = result.update(); //リザルト更新

                    // リザルト画面終了
                    if (num == 1)
                    {
                        game.destroy(); //ゲーム内の情報をすべて破棄
                        bikerand = false; //バイクのランダム生成を開始
                        work_no = kTitleInit; //タイトルへ
                    }
                    else if (num == 2)
                    {
                        exit = true;
                    }

                    break;
                }

                //画面クリア
                Direct3D::clear();

                //スプライト描画開始
                Sprite::begin();

                switch (work_no)
                {
                case kTitleUpdate:
                    title.draw();  //タイトル背景
                    title.dpaddraw();  //タイトル十字
                    title.buttondraw(); //タイトルAボタン
                    break;
                case kStartUpdate:
                    start.draw();  //説明
                    break;
                case kGameUpdate:
                    game.draw(oba); //ゲーム部分描画
                    break;
                case kHitSceneUpdate:
                    break;
                case kResultUpdate:
                    result.draw();       //背景
                    result.scoredraw1(); //1Pのスコア描画
                    result.scoredraw2(); //2Pのスコア描画
                    result.arrowdraw();  //リザルト矢印
                    break;

                }

                //スプライト描画終了
                Sprite::end();

                //画面更新              
                Direct3D::present();    //描画更新

            }
        }
    }
    
    //COMライブラリの開放
    CoUninitialize();

    //インターフェースの解放（確保した順の逆に開放していく)
    title.destroy();
    result.destroy();
    game.destroy();

    Common::destroy();
    Sprite::destroy();
    Direct3D::destroy();
    Adx::destroy();

    return 0;
}
// コールバック関数
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
            //ESCが押されたらループを終了する
            PostMessage( hWnd, WM_CLOSE, 0, 0 );
            break;

        }
        break;
    }

    return DefWindowProc( hWnd, Msg, wParam, lParam );

}