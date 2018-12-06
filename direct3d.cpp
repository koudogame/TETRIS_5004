#include"direct3d.h"

//メンバ変数の実体を宣言
ID3D11Device*           Direct3D::d3d_device_;                                                        //D3Dデバイスインターフェース
ID3D11DeviceContext*    Direct3D::device_context_;                                                    //デバイスコンテキストインターフェース
IDXGISwapChain*         Direct3D::swap_chain_;                                                        //スワップチェーンインターフェース
D3D_FEATURE_LEVEL       Direct3D::feature_level_;                                                     //機能レベル
ID3D11RenderTargetView* Direct3D::render_target_view_;                                                //描画ターゲットビュー

//初期化
bool Direct3D::init( const HWND hWnd )
{

    //機能レベルの設定
    D3D_FEATURE_LEVEL level[] =
    {
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_1
    };

    //スワップチェーンの設定
    DXGI_SWAP_CHAIN_DESC sc;
    ZeroMemory( &sc, sizeof( DXGI_SWAP_CHAIN_DESC ) );                                      //初期化
    sc.Windowed = true;                                                                     //ウィンドウモードの設定
    sc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;                                               //スワップエフェクト
    sc.OutputWindow = hWnd;                                                                 //ウィンドウハンドルの設定
    sc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;                                       //バックバッファの使用方法
    sc.BufferCount = 1U;                                                                    //バックバッファの数
    sc.BufferDesc.Width = 1280U;                                                            //バックバッファサイズ（横）
    sc.BufferDesc.Height = 720U;                                                            //バックバッファサイズ（縦）
    sc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;                                      //バックバッファフォーマット
    sc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;                                  //スケーリングモード
    sc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;                  //スキャンライン描画モード
    sc.BufferDesc.RefreshRate.Numerator = 60U;                                              //リフレッシュレート（分子）
    sc.BufferDesc.RefreshRate.Denominator = 1U;                                             //リフレッシュレート（分母）
    sc.SampleDesc.Count = 1;                                                                //マルチサンプリング
    sc.SampleDesc.Quality = 0;                                                              //マルチサンプリング品質
    sc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;                                      //モード設定

        //各種インターフェースの作成
    if( FAILED( D3D11CreateDeviceAndSwapChain(
        NULL,                                                                               //DXGIアダプター
        D3D_DRIVER_TYPE_HARDWARE,                                                           //ドライバータイプ
        NULL,                                                                               //ソフトウェアラスタライザーDLLハンドル
        D3D11_CREATE_DEVICE_DEBUG,                                                          //オプションフラグ
        level,                                                                              //機能レベル
        3,                                                                                  //機能レベル個数
        D3D11_SDK_VERSION,                                                                  //常にこの値を指定
        &sc,                                                                                //スワップチェーン構造体ポインタ
        &swap_chain_,                                                                        //スワップチェーンインターフェース受取先ポインタ
        &d3d_device_,                                                                        //D3Dデバイスインターフェース受取先ポインタ
        &feature_level_,                                                                     //採用した機能レベル
        &device_context_ ) ) )                                                               //デバイスコンテキストインターフェース受取先ポインタ

    {
        //エラー
        return false;
    }
    //バックバッファ描画ターゲット取得
    ID3D11Texture2D* backbuffer = NULL;
    if( FAILED( swap_chain_->GetBuffer(
        0,
        __uuidof(ID3D11Texture2D),
        reinterpret_cast<void**>(&backbuffer) ) ) )
    {
        //エラー
        return false;
    }

    //描画ターゲットビューの作成
    if( FAILED( d3d_device_->CreateRenderTargetView(
        backbuffer,                                                                         //ビューでアクセスするリソース
        NULL,                                                                               //ビューの定義
        &render_target_view_ ) ) )                                                           //描画ターゲットビュー格納先ポインタ
    {
        //エラー
        return false;
    }

    //バックバッファ解放
    backbuffer->Release();

    //描画ターゲットビューを出力マネージャーの描画ターゲットとして設定
    device_context_->OMSetRenderTargets(
        1,                                                                                   //描画ターゲット数
        &render_target_view_,                                                                 //ターゲットビュー配列
        NULL );                                                                              //深度/ステンシルビュー

        //ビューポートの作成
    D3D11_VIEWPORT vp;
    vp.Width = 1280.0F;
    vp.Height = 720.0F;
    vp.MinDepth = 0.0F;
    vp.MaxDepth = 1.0F;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    device_context_->RSSetViewports( 1, &vp );

    return true;
}

//破棄関数
void Direct3D::destroy()
{
    //インターフェースの解放
    render_target_view_->Release();
    swap_chain_->Release();
    device_context_->ClearState();
    device_context_->Release();
    d3d_device_->Release();

}

//描画クリア関数
void Direct3D::clear()
{
    float color[] = { 0.0F,0.0F,0.0F,1.0F };
    device_context_->ClearRenderTargetView( render_target_view_, color );
}

//画面更新関数
void Direct3D::present()
{
    swap_chain_->Present( 1, 0 );
}