#include"directshow.h"

 
 
 
/*
    DirectShowで音声を再生する
*/
//int _tmain
//(
//      int argc
//    , _TCHAR* argv[]
//)
//{
//    // std::wcoutのロケールを設定
//    std::wcout.imbue( std::locale( "", std::locale::ctype ) );
// 
//    // エラーコード
//    HRESULT hResult = S_OK;
// 
//    // COMを初期化
//    ::CoInitialize( NULL );
// 
//    // 再生する音声ファイル
//    std::wstring strFilePath = L".??TestData??Kalimba.mp3";
// 
//    // IGraphBuilder
//    IGraphBuilder* pGraphBuilder = NULL;
// 
//    // IMediaControl
//    IMediaControl *pMediaControl = NULL;
// 
//    // FilterGraphを生成
//    hResult = ::CoCreateInstance(
//              CLSID_FilterGraph
//            , NULL
//            , CLSCTX_INPROC
//            , IID_IGraphBuilder
//            , (LPVOID *)&pGraphBuilder
//        );
//    if ( !SUCCEEDED( hResult ) ) {
// 
//        // エラー
//    }
// 
//    // IMediaControlの取得
//    hResult = pGraphBuilder->QueryInterface(
//              IID_IMediaControl
//            , (void**)&pMediaControl
//        );
//    if ( !SUCCEEDED( hResult ) ) {
// 
//        // エラー
//    }
// 
//    // FilterGraphの生成
//    hResult = pMediaControl->RenderFile( (BSTR)strFilePath.c_str() );
//    if ( !SUCCEEDED( hResult ) ) {
// 
//        // エラー
//    }
// 
//    // 動画の再生
//    hResult = pMediaControl->Run();
//    if ( !SUCCEEDED( hResult ) ) {
// 
//        // エラー
//    }
// 
//    // 音声再生待ち
// 
// 
//    // IMediaControlの破棄
//    if ( NULL != pMediaControl ) {
//        pMediaControl->Release();
//    }
// 
//    // IGraphBuilderの破棄
//    if ( NULL != pGraphBuilder ) {
//        pGraphBuilder->Release();
//    }
// 
//    // COMの終了
//    ::CoUninitialize();
//}