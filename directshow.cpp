#include"directshow.h"

 
 
 
/*
    DirectShow�ŉ������Đ�����
*/
//int _tmain
//(
//      int argc
//    , _TCHAR* argv[]
//)
//{
//    // std::wcout�̃��P�[����ݒ�
//    std::wcout.imbue( std::locale( "", std::locale::ctype ) );
// 
//    // �G���[�R�[�h
//    HRESULT hResult = S_OK;
// 
//    // COM��������
//    ::CoInitialize( NULL );
// 
//    // �Đ����鉹���t�@�C��
//    std::wstring strFilePath = L".??TestData??Kalimba.mp3";
// 
//    // IGraphBuilder
//    IGraphBuilder* pGraphBuilder = NULL;
// 
//    // IMediaControl
//    IMediaControl *pMediaControl = NULL;
// 
//    // FilterGraph�𐶐�
//    hResult = ::CoCreateInstance(
//              CLSID_FilterGraph
//            , NULL
//            , CLSCTX_INPROC
//            , IID_IGraphBuilder
//            , (LPVOID *)&pGraphBuilder
//        );
//    if ( !SUCCEEDED( hResult ) ) {
// 
//        // �G���[
//    }
// 
//    // IMediaControl�̎擾
//    hResult = pGraphBuilder->QueryInterface(
//              IID_IMediaControl
//            , (void**)&pMediaControl
//        );
//    if ( !SUCCEEDED( hResult ) ) {
// 
//        // �G���[
//    }
// 
//    // FilterGraph�̐���
//    hResult = pMediaControl->RenderFile( (BSTR)strFilePath.c_str() );
//    if ( !SUCCEEDED( hResult ) ) {
// 
//        // �G���[
//    }
// 
//    // ����̍Đ�
//    hResult = pMediaControl->Run();
//    if ( !SUCCEEDED( hResult ) ) {
// 
//        // �G���[
//    }
// 
//    // �����Đ��҂�
// 
// 
//    // IMediaControl�̔j��
//    if ( NULL != pMediaControl ) {
//        pMediaControl->Release();
//    }
// 
//    // IGraphBuilder�̔j��
//    if ( NULL != pGraphBuilder ) {
//        pGraphBuilder->Release();
//    }
// 
//    // COM�̏I��
//    ::CoUninitialize();
//}