#include"directshow.h"
void movie()
{

    HRESULT hRes = CoInitialize(NULL);

    if (FAILED(hRes))
    {
        //エラー
        Error::showDialog("COMの初期化に失敗");


    }


    // IGraphBuilderインターフェイスの取得
    /*hRes = CoCreateInstance(
        CLSID_FilterGraph,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_IGraphBuilder,
        (void **)(m_cpGraph.ToCreator())
    );*/

    if (FAILED(hRes))
        Error::showDialog("インターフェイスの取得に失敗");

}