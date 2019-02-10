#pragma once


//Class

class Direct3D
{
private:
    //インターフェースの宣言
    static ID3D11Device* d3d_device_;                                                               //D3Dデバイスインターフェース
    static ID3D11DeviceContext* device_context_;                                                    //デバイスコンテキストインターフェース
    static IDXGISwapChain* swap_chain_;                                                             //スワップチェーンインターフェース
    static D3D_FEATURE_LEVEL feature_level_;                                                        //機能レベル
    static ID3D11RenderTargetView* render_target_view_;                                             //描画ターゲットビュー

public:
    static bool init( const HWND hWnd );                                                            //初期化
    static void destroy();                                                                          //破棄
    static void clear();                                                                            //画面クリア
    static void present();                                                                          //画面更新

    //インターフェースの取得
    static ID3D11Device* getDevice()         { return d3d_device_; }
    static ID3D11DeviceContext* getContext() { return device_context_; }
    static IDXGISwapChain* getChain()        { return swap_chain_; }
};