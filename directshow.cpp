#include"directshow.h"
void movie()
{

    HRESULT hRes = CoInitialize(NULL);

    if (FAILED(hRes))
    {
        //�G���[
        Error::showDialog("COM�̏������Ɏ��s");


    }


    // IGraphBuilder�C���^�[�t�F�C�X�̎擾
    /*hRes = CoCreateInstance(
        CLSID_FilterGraph,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_IGraphBuilder,
        (void **)(m_cpGraph.ToCreator())
    );*/

    if (FAILED(hRes))
        Error::showDialog("�C���^�[�t�F�C�X�̎擾�Ɏ��s");

}