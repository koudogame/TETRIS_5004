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

//列挙体
enum
{
    kSceneInit,         //シーン変化初期化
    kSceneUpdate,       //シーン変化更新

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

    kResultUpdate,       // ゲーム終了

    kOptionInit,         //オプション初期化
    kOptionUpdate,       //オプション更新

    kRankingInit,        //ランキング初期化
    kRankingUpdate,      //ランキング更新

    k4ptetrisInit,       //4人テトリス初期化
    k4ptetrisUpdate      //4人テトリス更新

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
    int work_no = kSceneInit;

    //シーンクラス変数
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

                //更新処理
                Pad::update();
                Key::update();

                //シーン処理
                switch (work_no)
                {
                case kSceneInit:
                    if (!scene.init())
                    {
                        //エラー
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
                        //エラー
                        PostQuitMessage(0);
                    }
                    work_no = kCreditUpdate;
                    break;
                case kCreditUpdate:
                    ui.update();
                    if (!credit.update())
                    {
                        //タイトルへ戻る
                        work_no = kTitleUpdate;
                        credit.destroy();
                    }
                    break;
                case kGameInit:
                    //ゲームクラス初期化
                    if (!game.init())
                    {
                        //エラー
                        PostQuitMessage(0);
                    }

                    //次の処理へ
                    work_no = kGameUpdate;
                    break;

                case kGameUpdate:
                     gup = game.update(0);

                    if (gup == 3) //リセット
                    {
                        game.destroy();
                        work_no = kGameInit;
                    }
                    else if (gup == 4) //タイトルへ
                    {
                        game.destroy();
                        work_no = kTitleUpdate;
                    }
                     break;

                case kResultInit:
                    // 次の処理
                    work_no = kResultUpdate;
                    break;
                case kResultUpdate:
                    num = result.update(); //リザルト更新

                    // リザルト画面終了
                    if (num == 1)
                    {
                        game.destroy(); //ゲーム内の情報をすべて破棄
                        work_no = kTitleInit; //タイトルへ
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
                        //エラー
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

                //画面クリア
                Direct3D::clear();

                //スプライト描画開始
                Sprite::begin();

                switch (work_no)
                {
                case kSceneUpdate:
                    scene.draw();
                    break;
                case kTitleUpdate:
                    title.draw();  //タイトル背景
                    ui.inputdraw(Title_);
                    title.cursordraw(); //タイトルカーソル
                    break;
                case kStartUpdate:
                    start.draw();  //説明
                    break;
                case kGameUpdate:
                    game.draw(); //ゲーム部分描画
                    break;
                case kHitSceneUpdate:
                    break;
                case kResultUpdate:
                    result.draw();       //背景
                    ui.inputdraw(result_option);
                    break;
                case kCreditUpdate:
                    credit.draw(); //クレジット背景
                    ui.inputdraw(rank_credit);
                    break;
                case kOptionUpdate:
                    option.draw(); //オプション背景
                    option.cursordraw();
                    option.opdraw();
                    ui.inputdraw(result_option); //入力状態表示
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