#pragma once

#include<d3d11.h>
#include"release.h"
#include"player.h"

class Start
{
private:
    ID3D11ShaderResourceView* texture1_;         //1p��������
    ID3D11ShaderResourceView* texture2_;         //2p��������
    ID3D11ShaderResourceView* texture3_;         //����������
    ID3D11ShaderResourceView* texture4_;         //������������

public:

    Start();
    ~Start();

    //������
    bool init();                                //������
    bool update();                              //�X�V
    void draw();                                //�`��
    void destroy();                             //�j��

    //�t���O
    bool p1 = false;
    bool p2 = false;
	bool complete = false;

    //�J�E���g
    int cnt = 0;
};