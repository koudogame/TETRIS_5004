#pragma once

#include<d3d11.h>
#include"Release.h"

class Credit
{
private:
    ID3D11ShaderResourceView* texture_; //�e�N�X�`��
    ID3D11ShaderResourceView* Ctexture_; //�e�N�X�`��
    RECT trim;

public:
    //�R���X�g���N�^
    Credit() { texture_ = NULL; }

    bool init();        //������
    bool update();       //�X�V
    void draw();        //�`��
    void buttondraw();
    void destroy();     //�j��

    int menu = 0; //�Q�[�����I���Ƃ���true
    int cnt = 0;

};
